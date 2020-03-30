#include<iostream>
#include<fstream>
#include<vector>
#include <jni.h>
#include "compute-mfcc-feats.h"
#include "feat-util.h"

int no_of_mfcc_feats = 13;
int no_of_rows = 0;

extern "C" {
#include "svm-predict.h"
}

extern "C"
JNIEXPORT jintArray JNICALL
Java_test1_pantha_registrationform_MainActivity_AsthmaPredict(JNIEnv *env, jobject instance,
													 jstring wav_file_, jstring model_file_) {
	const char *wav_file = env->GetStringUTFChars(wav_file_, 0);
	const char *model_file = env->GetStringUTFChars(model_file_, 0);
	
	//Computing MFCC Features
	Matrix<BaseFloat> raw_mfcc = compute_mfcc_feats(wav_file);
	no_of_rows = raw_mfcc.NumRows();
	if(no_of_rows == 0){
        exit(-1);
    }

	//dummy labels
	int ref_label = 0;
	int* ref_labels = (int*)calloc(no_of_rows, sizeof(int));
	for (int i = 0; i < no_of_rows; i++) {
		*(ref_labels + i) = ref_label;
	}

	char feat_file[200];
    char out_file[200];
	strcpy(feat_file,wav_file);
	strcat(feat_file,".feat.txt");
	strcpy(out_file,wav_file);
	strcat(out_file,".out.txt");

	// Writing MFCC features to feat_file
	writeFeats(feat_file, raw_mfcc, ref_labels);

	//Loading SVM Model
	struct svm_model* my_model = svm_load_model(model_file);

	FILE* input = fopen(feat_file, "r");
	FILE* output = fopen(out_file, "w");

	// Evaluating the model
	predict(input, my_model, output);

	// Reading Predictions to storing them to a jni integer array.
	std::ifstream pred(out_file);
    std::string line;
    getline(pred,line);
    std::vector<int> labels;
    int x;
    std::string s1,s2;
    while(pred>>x>>s1>>s2){
        labels.push_back(x);
    }
    int n = labels.size();
    jintArray  ret = env->NewIntArray(n);
    if(ret == NULL){
        return NULL;
    }
    jint tmp[n];
    for(int i = 0;i<n;i++){
        tmp[i] = labels[i];
    }

    // Closing files
	fclose(input);
	fclose(output);
	// Removing temporary files
    remove(feat_file);
	remove(out_file);
	// Garbage collection
	free(ref_labels);

	env->SetIntArrayRegion(ret,0,n,tmp);
	env->ReleaseStringUTFChars(wav_file_, feat_file);
	env->ReleaseStringUTFChars(model_file_, model_file);
	
	return ret;
}

#include <compute-mfcc-feats.h>
#include "feat-util.h"

void writeFeats(const char* featfilename,Matrix<BaseFloat> feats,int* labels) {
	int nr = feats.NumRows();
	int nc = feats.NumCols();
	no_of_rows = nr;
	std::ofstream featfile(featfilename, std::ofstream::app);
	featfile.precision(4);
	featfile << std::fixed;
	for (int i = 0; i < no_of_rows; i++) {
		SubVector<BaseFloat> row = feats.Row(i);
		featfile << *(labels + i) << " ";
		int index = 1;
		for (int j = 0; j < no_of_mfcc_feats; j++) {
			if (j % 13 != 0) {
                double gg = row.Data()[j];
                featfile << (index++) << ":" << gg << " ";
            }
		}
		featfile << "\n";
	}
	featfile.flush();
	featfile.close();
}
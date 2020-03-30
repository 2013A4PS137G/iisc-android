package test1.pantha.registrationform;

import android.content.res.AssetManager;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.widget.Button;

import java.io.File;
import java.io.FileOutputStream;
import java.io.InputStream;

public class MainActivity extends AppCompatActivity {
    static {
        System.loadLibrary("asthma-lib");
    }

    Button button1,button2,button3;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        test();
    }

    private void test(){
        String cdir = getCacheDir().getPath();
        loadAssets();
        int[] predictions = AsthmaPredict(cdir+"/test.wav",cdir+"/model.txt");
    }

    private void loadAssets(){
        String cdir = getCacheDir().getPath();
        AssetManager my_assets = getAssets();
        String assets[] = {"model.txt","test.wav"};
        for(int i = 0;i<assets.length;i++) {
            File f = new File(cdir+"/" + assets[i]);
            if (!f.exists()) try {

                InputStream is = my_assets.open(assets[i]);
                int size = is.available();
                byte[] buffer = new byte[size];
                is.read(buffer);
                is.close();


                FileOutputStream fos = new FileOutputStream(f);
                fos.write(buffer);
                fos.close();
            } catch (Exception e) { throw new RuntimeException(e); }
        }
    }

    public native int[] AsthmaPredict(String wav_file, String model_file);
}

#include <feat-util.h>
#include "compute-mfcc-feats.h"

Matrix<BaseFloat> compute_mfcc_feats(const char* audiofilepath)
{
	try {
		MfccOptions mfcc_opts;
		mfcc_opts.frame_opts.frame_length_ms = 20;
		mfcc_opts.frame_opts.frame_shift_ms = 10;
		
		BaseFloat vtln_warp = 1.0;
		std::string vtln_map_rspecifier;
		int32 channel = -1;
		BaseFloat min_duration = 0.0;

		Mfcc mfcc(mfcc_opts);

		Input wavFile;
		wavFile.Open(audiofilepath);
		WaveHolder holder;
		holder.Read(wavFile.Stream());
		const WaveData wave_data = holder.Value();
		wavFile.Close();

		if (wave_data.Duration() < min_duration) {
			KALDI_WARN << "File is too short ("
				<< wave_data.Duration() << " sec): producing no output.";
			exit(-1);
		}

		int32 num_chan = wave_data.Data().NumRows(), this_chan = channel;

		{  // This block works out the channel (0=left, 1=right...)
			KALDI_ASSERT(num_chan > 0);  // should have been caught in
			// reading code if no channels.
			if (channel == -1) {
				this_chan = 0;
				if (num_chan != 1)
					KALDI_WARN << "Channel not specified but you have data with "
					<< num_chan << " channels; defaulting to zero";
			}
			else {
				if (this_chan >= num_chan) {
					KALDI_WARN << "File has "
						<< num_chan << " channels but you specified channel "
						<< channel << ", producing no output.";
					exit(-1);
				}
			}
		}

		SubVector<BaseFloat> waveform(wave_data.Data(), this_chan);
		Matrix<BaseFloat> features;
		int samp_freq = wave_data.SampFreq();
			
		mfcc.ComputeFeatures(waveform, samp_freq, 1.0, &features);

		KALDI_LOG << "Computed MFCCs for " << audiofilepath;

		return features;
	}
	catch (const std::exception &e) {
		std::cerr << e.what();
		exit(-1);
	}
}

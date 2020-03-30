#pragma once

#include "base/kaldi-common.h"
#include "util/common-utils.h"
#include "feat/feature-mfcc.h"
#include "feat/wave-reader.h"
#include "feat/resample.h"
#include "matrix/kaldi-matrix.h"
#include "transform/cmvn.h"

using namespace kaldi;

extern int samp_freq;
Matrix<BaseFloat> compute_mfcc_feats(const char* audiofilepath);

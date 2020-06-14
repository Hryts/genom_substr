//
// Created by kurlyana on 14.06.2020.
//

#include "result_struct.h"

void updateResult(Result &globalRes, Result &localRes) {
    globalRes.result.insert(localRes.result.begin(), localRes.result.end());
}


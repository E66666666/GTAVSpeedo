// Copyright (c) 2014, Jan Winkler <winkler@cs.uni-bremen.de>
// All rights reserved.
//
// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions are met:
//
//     * Redistributions of source code must retain the above copyright
//       notice, this list of conditions and the following disclaimer.
//     * Redistributions in binary form must reproduce the above copyright
//       notice, this list of conditions and the following disclaimer in the
//       documentation and/or other materials provided with the distribution.
//     * Neither the name of Universität Bremen nor the names of its
//       contributors may be used to endorse or promote products derived from
//       this software without specific prior written permission.
//
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
// AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
// IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
// ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE
// LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
// CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
// SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
// INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
// CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
// ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
// POSSIBILITY OF SUCH DAMAGE.

/* Author: Jan Winkler */

#include "Colors.h"
#include <algorithm>

using namespace Utils::Colors;

ColorHSV Utils::Colors::RGBtoHSV(ColorRGB rgb) {
    ColorHSV hsv{};
    auto fR = rgb.R;
    auto fG = rgb.G;
    auto fB = rgb.B;

    auto fCMax = std::max(std::max(fR, fG), fB);
    auto fCMin = std::min(std::min(fR, fG), fB);
    auto fDelta = fCMax - fCMin;

    if (fDelta > 0) {
        if (fCMax == fR) {
            hsv.H = 60.0 * (fmod(((fG - fB) / fDelta), 6.0));
        }
        else if (fCMax == fG) {
            hsv.H = 60.0 * (((fB - fR) / fDelta) + 2.0);
        }
        else if (fCMax == fB) {
            hsv.H = 60.0 * (((fR - fG) / fDelta) + 4.0);
        }

        if (fCMax > 0.0) {
            hsv.S = fDelta / fCMax;
        }
        else {
            hsv.S = 0.0;
        }

        hsv.V = fCMax;
    }
    else {
        hsv.H = 0.0;
        hsv.S = 0.0;
        hsv.V = fCMax;
    }

    if (hsv.H < 0.0) {
        hsv.H = 360.0 + hsv.H;
    }
    return hsv;
}

ColorRGB Utils::Colors::HSVtoRGB(ColorHSV hsv) {
    ColorRGB rgb{};
    auto fH = hsv.H;
    auto fS = hsv.S;
    auto fV = hsv.V;

    auto fC = fV * fS; // Chroma
    auto fHPrime = fmod(fH / 60.0, 6.0);
    auto fX = fC * (1.0 - fabs(fmod(fHPrime, 2.0) - 1.0));
    auto fM = fV - fC;

    if (0.0 <= fHPrime && fHPrime < 1.0) {
        rgb.R = fC;
        rgb.G = fX;
        rgb.B = 0.0;
    }
    else if (1.0 <= fHPrime && fHPrime < 2.0) {
        rgb.R = fX;
        rgb.G = fC;
        rgb.B = 0.0;
    }
    else if (2.0 <= fHPrime && fHPrime < 3.0) {
        rgb.R = 0.0;
        rgb.G = fC;
        rgb.B = fX;
    }
    else if (3.0 <= fHPrime && fHPrime < 4.0) {
        rgb.R = 0.0;
        rgb.G = fX;
        rgb.B = fC;
    }
    else if (4.0 <= fHPrime && fHPrime < 5.0) {
        rgb.R = fX;
        rgb.G = 0.0;
        rgb.B = fC;
    }
    else if (5.0 <= fHPrime && fHPrime < 6.0) {
        rgb.R = fC;
        rgb.G = 0.0;
        rgb.B = fX;
    }
    else {
        rgb.R = 0.0;
        rgb.G = 0.0;
        rgb.B = 0.0;
    }

    rgb.R += fM;
    rgb.G += fM;
    rgb.B += fM;

    return rgb;
}

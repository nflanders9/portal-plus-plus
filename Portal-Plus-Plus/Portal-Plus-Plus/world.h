#ifndef WORLD
#define WORLD

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <string>
#include <fstream>
#include <iostream>

using namespace sf;

const std::string ASSET_DIR = "../assets";

const int UNIT = 32;

float static offsetX = 0;
float static offsetY = 0;

const int H = 18;
const int W = 40;

String static TileMap[H] = {
	"WWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWW",
	"W                         FFF          W",
	"W                         FFF          W",
	"W                         FFF          W",
	"W                         FFF          W",
	"W                         FFF          W",
	"W                         FFF          W",
	"W                                      W",
	"W                                      W",
	"W                         FFF          W",
	"W                         FFF          W",
	"W                         WWW          W",
	"W        0    X    0      WWW          W",
	"W         FFFFFFFFF       WWW          W",
	"W       FFFFFFFFFFFF      WWW     E    W",
	"W P    FFFFFFFFFFFFFF     WWW          W",
	"WWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWW",
	"WWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWW"
};

String static Level1[H] = {
	"WWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWW",
	"WFFFFFWWWWFFFFFFFFFFFFFFFFFFFFFFFFFFFFFW",
	"WF                                     W",
	"WW                                     W",
	"WW                                     W",
	"WW                                     W",
	"WF                              E      W",
	"WF                                     W",
	"WF            FFFFFFFFWWWWWWWWWWWWWWWWWW",
	"WF            FFFFFFFFFFFFFFFFFFFFFFFFFW",
	"WF            FFFFFFFFFFFFFFFFFFFFFFFFFW",
	"WF            FFFFFFFFFFFFFFFFFFFFFFFFFW",
	"WF            FFFFFFFFFFFFFFFFFFFFFFFFFW",
	"WF            FFFFFFFFFFFFFFFFFFFFFFFFFW",
	"WF            FFFFFFFFFFFFFFFFFFFFFFFFFW",
	"WF P          FFFFFFFFFFFFFFFFFFFFFFFFFW",
	"WFFFFFWWWWFFFFFWWWWWWWWWWWWWWWWWWWWWWWWW",
	"WWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWW"
};

String static Level2[H] = {
	"WWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWW",
	"W                         FFF          W",
	"W                         FFF          W",
	"W                         FFF          W",
	"W                         FFF          W",
	"W                         FFF          W",
	"W                         FFF          W",
	"W                                      W",
	"W                                      W",
	"W                         FFF          W",
	"W                         FFF          W",
	"W                         WWW          W",
	"W        0    X    0      WWW          W",
	"W         FFFFFFFFF       WWW          W",
	"W       FFFFFFFFFFFF      WWW     E    W",
	"W P    FFFFFFFFFFFFFF     WWW          W",
	"WWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWW",
	"WWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWW"
};

String static Level3[H] = {
	"WWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWW",
	"W                                      W",
	"W                                      W",
	"W P                                    W",
	"WFFFFFFFFFFFFFFFFFFFFFFFFFF  FFFFFFFFFFW",
	"WFFFFFFFFFFFFFFFFFF   X   X    X     X W",
	"WFFFFFFFFFFFFFFFFFFFFFFFFFF  FFFFFFFFFFW",
	"WFFFFFFFFFFFFFFFFFF     X      X   X   W",
	"WFFFFFFFFFFFFFFFFFFFFFFFFFF  FFFFFFFFFFW",
	"WFFFFFFFFFFFFFFFFFF  X X  X      X     W",
	"WFFFFFFFFFFFFFFFFFFFFFFFFFF  FFFFFFFFFFW",
	"WFFFFFFFFFFFFFFFFFFX   X  X            W",
	"WFFFFFFFFFFFFFFFFFFFFFFFFFF  FFFFFFFFFFW",
	"WFFFFFFFFFFFFFFFFFF                    W",
	"WFFFFFFFFFFFFFFFFFF                E   W",
	"WFFFFFFFFFFFFFFFFFF                    W",
	"WWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWW",
	"WWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWW"
};

String static Level4[H] = {
	"WWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWW",
	"WFFFWWWWWFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFW",
	"W                                      W",
	"W                                      W",
	"W                                 E    W",
	"W                                      W",
	"W     FFFFFFFFFFFF     FFFFFFFFFFFFFFFFW",
	"W     FFFFFFFFFFFF     WFFFFFFFFFFFFFFFW",
	"W     FFFFFFFFFFFF     WFFFFFFFFFFFFFFFW",
	"W     FFFFFFFFFFFF     WFFFFFFFFFFFFFFFW",
	"W     FFFFFFFFFFFF     WFFFFFFFFFFFFFFFW",
	"W     FFFFFFFFFFFF     WFFFFFFFFFFFFFFFW",
	"W     FFFFFFFFFFFF     WFFFFFFFFFFFFFFFW",
	"W     FFFFFFFFFFFF     WFFFFFFFFFFFFFFFW",
	"W                      WFFFFFFFFFFFFFFFW",
	"W P          X     X   WFFFFFFFFFFFFFFFW",
	"WFFFFFFFFFFFFFFFFFWWWWWWFFFFFFFFFFFFFFFW",
	"WWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWW"
};

String static Level5[H] = {
	"WWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWW",
	"WFFFFFFFFFFFFFFFFFFFFFFFWWWWWWWWWWWWWWWW",
	"WFFFFFFFFFFFFFFFFFFFFFFF        E     WW",
	"WFFWWWFFFWFFFWFFWFWWWWFF              WW",
	"WFFWFFFFWFWFFWFWFFWFFFFF  FFFFFFFFFFFFFW",
	"WFFWFFFFWWWFFWWFFFWWWFFF  FFFFFFFFFFFFFW",
	"WFFWFFFWFFFWFWFWFFWFFFFF  FFFFFFFFFFFFFW",
	"WFFWWWFWFFFWFWFFWFWWWWFF  FWFFFWWWFWWWFW",
	"WFFFFFFFFFFFFFFFFFFFFFFF  FWFFFFWFFWFFFW",
	"WFFFFFFFFFFFFFFFFFFFFFFF  FWFFFFWFFWWFFW",
	"WFFWWWFFWWWFFFFFFWFFFFFF  FWFFFFWFFWFFFW",
	"WFFFWFFWFFFFFFFFWFWFFFFF  FWWWFWWWFWWWFW",
	"WFFFWFFFWWFFFFFFWWWFFFFF  FFFFFFFFFFFFFW",
	"WFFFWFFFFFWFFFFWFFFWFFFF  FFFFFFFFFFFFFW",
	"WFFWWWFWWWFFFFFWFFFWFFFF  FFFFFFFFFFFFFW",
	"W                         WFFFFFFFFFFFFW",
	"W  P    X X X X X X X X   WFFFFFFFFFFFFW",
	"WWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWW"
};
#endif // WORLD


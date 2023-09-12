#include <Arduino.h>
#include "SPI.h"
#include "Adafruit_GFX.h"
#include "Adafruit_ILI9341.h"
#include "device.h"

//closed
const uint16_t symbol1[324] = {
    0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0x8410,
    0xffff, 0xffff, 0xffdf, 0xffdf, 0xffdf, 0xffdf, 0xffdf, 0xffdf, 0xffdf, 0xffdf, 0xffdf, 0xffdf, 0xffdf, 0xffdf, 0xffdf, 0xce79, 0x8410, 0x8410,
    0xffff, 0xffdf, 0xc638, 0xc638, 0xc638, 0xc638, 0xc638, 0xc638, 0xc638, 0xc638, 0xc638, 0xc638, 0xc638, 0xc638, 0xc638, 0x8430, 0x8410, 0x8410,
    0xffff, 0xffdf, 0xc638, 0xc638, 0xc638, 0xc638, 0xc638, 0xc638, 0xc638, 0xc638, 0xc638, 0xc638, 0xc638, 0xc638, 0xc638, 0x8430, 0x8410, 0x8410,
    0xffff, 0xffdf, 0xc638, 0xc638, 0xc638, 0xc638, 0xc638, 0xc638, 0xc638, 0xc638, 0xc638, 0xc638, 0xc638, 0xc638, 0xc638, 0x8430, 0x8410, 0x8410,
    0xffff, 0xffdf, 0xc638, 0xc638, 0xc638, 0xc638, 0xc638, 0xc638, 0xc638, 0xc638, 0xc638, 0xc638, 0xc638, 0xc638, 0xc638, 0x8430, 0x8410, 0x8410,
    0xffff, 0xffdf, 0xc638, 0xc638, 0xc638, 0xc638, 0xc638, 0xc638, 0xc638, 0xc638, 0xc638, 0xc638, 0xc638, 0xc638, 0xc638, 0x8430, 0x8410, 0x8410,
    0xffff, 0xffdf, 0xc638, 0xc638, 0xc638, 0xc638, 0xc638, 0xc638, 0xc638, 0xc638, 0xc638, 0xc638, 0xc638, 0xc638, 0xc638, 0x8430, 0x8410, 0x8410,
    0xffff, 0xffdf, 0xc638, 0xc638, 0xc638, 0xc638, 0xc638, 0xc638, 0xc638, 0xc638, 0xc638, 0xc638, 0xc638, 0xc638, 0xc638, 0x8430, 0x8410, 0x8410,
    0xffff, 0xffdf, 0xc638, 0xc638, 0xc638, 0xc638, 0xc638, 0xc638, 0xc638, 0xc638, 0xc638, 0xc638, 0xc638, 0xc638, 0xc638, 0x8430, 0x8410, 0x8410,
    0xffff, 0xffdf, 0xc638, 0xc638, 0xc638, 0xc638, 0xc638, 0xc638, 0xc638, 0xc638, 0xc638, 0xc638, 0xc638, 0xc638, 0xc638, 0x8430, 0x8410, 0x8410,
    0xffff, 0xffdf, 0xc638, 0xc638, 0xc638, 0xc638, 0xc638, 0xc638, 0xc638, 0xc638, 0xc638, 0xc638, 0xc638, 0xc638, 0xc638, 0x8430, 0x8410, 0x8410,
    0xffff, 0xffdf, 0xc638, 0xc638, 0xc638, 0xc638, 0xc638, 0xc638, 0xc638, 0xc638, 0xc638, 0xc638, 0xc638, 0xc638, 0xc638, 0x8430, 0x8410, 0x8410,
    0xffff, 0xffdf, 0xc638, 0xc638, 0xc638, 0xc638, 0xc638, 0xc638, 0xc638, 0xc638, 0xc638, 0xc638, 0xc638, 0xc638, 0xc638, 0x8430, 0x8410, 0x8410,
    0xffff, 0xffdf, 0xc638, 0xc638, 0xc638, 0xc638, 0xc638, 0xc638, 0xc638, 0xc638, 0xc638, 0xc638, 0xc638, 0xc638, 0xc638, 0x8430, 0x8410, 0x8410,
    0xffff, 0xffdf, 0xc638, 0xc638, 0xc638, 0xc638, 0xc638, 0xc638, 0xc638, 0xc638, 0xc638, 0xc638, 0xc638, 0xc638, 0xc638, 0x8430, 0x8410, 0x8410,
    0xce79, 0x8410, 0x8410, 0x8410, 0x8410, 0x8410, 0x8410, 0x8410, 0x8410, 0x8410, 0x8410, 0x8410, 0x8410, 0x8410, 0x8410, 0x8410, 0x8410, 0x8410,
    0x8410, 0x8410, 0x8410, 0x8410, 0x8410, 0x8410, 0x8410, 0x8410, 0x8410, 0x8410, 0x8410, 0x8410, 0x8410, 0x8410, 0x8410, 0x8410, 0x8410, 0x8410

};

//mine
const uint16_t symbol2[324] = {
    0x8410, 0x8410, 0x8410, 0x8410, 0x8410, 0x8410, 0x8410, 0x8410, 0x8410, 0x8410, 0x8410, 0x8410, 0x8410, 0x8410, 0x8410, 0x8410, 0x8410, 0x8410,
    0x8410, 0x94b2, 0xa534, 0xa534, 0xa534, 0xa534, 0xa534, 0xa534, 0xa534, 0xa534, 0xa534, 0xa534, 0xa534, 0xa534, 0xa534, 0xa534, 0xa534, 0xa534,
    0x8410, 0xa534, 0xc638, 0xc638, 0xc638, 0xc638, 0xc638, 0xc638, 0xc618, 0x0000, 0x8c51, 0xc638, 0xc638, 0xc638, 0xc638, 0xc638, 0xc638, 0xc638,
    0x8410, 0xa534, 0xc638, 0xc638, 0xc638, 0xc638, 0xc638, 0xc638, 0xc618, 0x0000, 0x8c51, 0xc638, 0xc638, 0xc638, 0xc638, 0xc638, 0xc638, 0xc638,
    0x8410, 0xa534, 0xc638, 0xc638, 0xc638, 0xc638, 0xc638, 0xc638, 0xa514, 0x0000, 0x2124, 0xc638, 0xc638, 0xc638, 0xc638, 0xc638, 0xc638, 0xc638,
    0x8410, 0xa534, 0xc638, 0xc638, 0xc638, 0x0000, 0x0861, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0861, 0x0000, 0xb5b6, 0xc638, 0xc638, 0xc638,
    0x8410, 0xa534, 0xc638, 0xc638, 0xc638, 0x1082, 0x0000, 0x0000, 0x2144, 0x10a2, 0x0000, 0x0000, 0x0000, 0x0000, 0xc638, 0xc638, 0xc638, 0xc638,
    0x8410, 0xa534, 0xc638, 0xc638, 0xc638, 0x0000, 0x0000, 0x3a07, 0x8430, 0x634c, 0x2985, 0x0000, 0x0000, 0x0000, 0xc638, 0xc638, 0xc638, 0xc638,
    0x8410, 0xa534, 0xc618, 0xc618, 0xc618, 0x0000, 0x31a5, 0x94b2, 0xffff, 0xdedb, 0x73ce, 0x0000, 0x0000, 0x0000, 0x8430, 0xc618, 0xc618, 0xc638,
    0x8410, 0xa534, 0x0000, 0x0000, 0x0000, 0x0000, 0x2144, 0x7bee, 0xef3c, 0xbdf7, 0x634c, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0xc638,
    0x8410, 0xa534, 0x8c51, 0x8c71, 0x8c71, 0x0000, 0x0000, 0x3a27, 0x8450, 0x636c, 0x2985, 0x0000, 0x0000, 0x0000, 0x5acb, 0x8c71, 0x8c71, 0xc638,
    0x8410, 0xa534, 0xc638, 0xc638, 0xc638, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0xc638, 0xc638, 0xc638, 0xc638,
    0x8410, 0xa534, 0xc638, 0xc638, 0xc638, 0x18c3, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0xc638, 0xc638, 0xc638, 0xc638,
    0x8410, 0xa534, 0xc638, 0xc638, 0xc638, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0xc638, 0xc638, 0xc638, 0xc638,
    0x8410, 0xa534, 0xc638, 0xc638, 0xc638, 0xb5b6, 0xc638, 0xc638, 0x9492, 0x0000, 0x6b4d, 0xc638, 0xc638, 0xc638, 0xb5b6, 0xc638, 0xc638, 0xc638,
    0x8410, 0xa534, 0xc638, 0xc638, 0xc638, 0xc638, 0xc638, 0xc638, 0xc618, 0x0000, 0x8c51, 0xc638, 0xc638, 0xc638, 0xc638, 0xc638, 0xc638, 0xc638,
    0x8410, 0xa534, 0xc638, 0xc638, 0xc638, 0xc638, 0xc638, 0xc638, 0xc618, 0x0000, 0x8c51, 0xc638, 0xc638, 0xc638, 0xc638, 0xc638, 0xc638, 0xc638,
    0x8410, 0xa534, 0xc638, 0xc638, 0xc638, 0xc638, 0xc638, 0xc638, 0xc638, 0xc638, 0xc638, 0xc638, 0xc638, 0xc638, 0xc638, 0xc638, 0xc638, 0xc638

};

//unknown
const uint16_t symbol3[324] = {
    0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0x8410,
    0xffff, 0xffff, 0xffdf, 0xffdf, 0xffdf, 0xffdf, 0xffdf, 0xffdf, 0xffdf, 0xffdf, 0xffdf, 0xffdf, 0xffdf, 0xffdf, 0xffdf, 0xce79, 0x8410, 0x8410,
    0xffff, 0xffdf, 0xc638, 0xc638, 0xc638, 0xc638, 0xc638, 0xc638, 0xc638, 0xc638, 0xc638, 0xc638, 0xc638, 0xc638, 0xc638, 0x8430, 0x8410, 0x8410,
    0xffff, 0xffdf, 0xc638, 0xc638, 0xc638, 0xc638, 0xc638, 0xc638, 0xc638, 0xc638, 0xc638, 0xc638, 0xc638, 0xc638, 0xc638, 0x8430, 0x8410, 0x8410,
    0xffff, 0xffdf, 0xc638, 0xc638, 0xc638, 0xc638, 0x0000, 0x0000, 0x0000, 0x0000, 0xc638, 0xc638, 0xc638, 0xc638, 0xc638, 0x8430, 0x8410, 0x8410,
    0xffff, 0xffdf, 0xc638, 0xc638, 0xc638, 0x0000, 0x0000, 0xc638, 0xc638, 0x0000, 0x0000, 0xc638, 0xc638, 0xc638, 0xc638, 0x8430, 0x8410, 0x8410,
    0xffff, 0xffdf, 0xc638, 0xc638, 0xc638, 0x0000, 0xc638, 0xc638, 0xc638, 0xc638, 0x0000, 0xc638, 0xc638, 0xc638, 0xc638, 0x8430, 0x8410, 0x8410,
    0xffff, 0xffdf, 0xc638, 0xc638, 0xc638, 0xc638, 0xc638, 0xc638, 0xc638, 0x0000, 0x0000, 0xc638, 0xc638, 0xc638, 0xc638, 0x8430, 0x8410, 0x8410,
    0xffff, 0xffdf, 0xc638, 0xc638, 0xc638, 0xc638, 0xc638, 0xc638, 0x0000, 0x0000, 0xc638, 0xc638, 0xc638, 0xc638, 0xc638, 0x8430, 0x8410, 0x8410,
    0xffff, 0xffdf, 0xc638, 0xc638, 0xc638, 0xc638, 0xc638, 0xc638, 0x0000, 0xc638, 0xc638, 0xc638, 0xc638, 0xc638, 0xc638, 0x8430, 0x8410, 0x8410,
    0xffff, 0xffdf, 0xc638, 0xc638, 0xc638, 0xc638, 0xc638, 0xc638, 0x0000, 0xc638, 0xc638, 0xc638, 0xc638, 0xc638, 0xc638, 0x8430, 0x8410, 0x8410,
    0xffff, 0xffdf, 0xc638, 0xc638, 0xc638, 0xc638, 0xc638, 0xc638, 0xc638, 0xc638, 0xc638, 0xc638, 0xc638, 0xc638, 0xc638, 0x8430, 0x8410, 0x8410,
    0xffff, 0xffdf, 0xc638, 0xc638, 0xc638, 0xc638, 0xc638, 0xc638, 0x0000, 0xc638, 0xc638, 0xc638, 0xc638, 0xc638, 0xc638, 0x8430, 0x8410, 0x8410,
    0xffff, 0xffdf, 0xc638, 0xc638, 0xc638, 0xc638, 0xc638, 0xc638, 0x0000, 0xc638, 0xc638, 0xc638, 0xc638, 0xc638, 0xc638, 0x8430, 0x8410, 0x8410,
    0xffff, 0xffdf, 0xc638, 0xc638, 0xc638, 0xc638, 0xc638, 0xc638, 0xc638, 0xc638, 0xc638, 0xc638, 0xc638, 0xc638, 0xc638, 0x8430, 0x8410, 0x8410,
    0xffff, 0xffdf, 0xc638, 0xc638, 0xc638, 0xc638, 0xc638, 0xc638, 0xc638, 0xc638, 0xc638, 0xc638, 0xc638, 0xc638, 0xc638, 0x8430, 0x8410, 0x8410,
    0xce79, 0x8410, 0x8410, 0x8410, 0x8410, 0x8410, 0x8410, 0x8410, 0x8410, 0x8410, 0x8410, 0x8410, 0x8410, 0x8410, 0x8410, 0x8410, 0x8410, 0x8410,
    0x8410, 0x8410, 0x8410, 0x8410, 0x8410, 0x8410, 0x8410, 0x8410, 0x8410, 0x8410, 0x8410, 0x8410, 0x8410, 0x8410, 0x8410, 0x8410, 0x8410, 0x8410

};

//flag
const uint16_t symbol4[324] = {
    0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xc638,
    0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0x8410,
    0xffff, 0xffff, 0xc638, 0xc638, 0xc638, 0xc638, 0xc638, 0xc638, 0xc638, 0xc638, 0xc638, 0xc638, 0xc638, 0xc638, 0xc638, 0xc638, 0x8430, 0x8410,
    0xffff, 0xffff, 0xc638, 0xc638, 0xc638, 0xc638, 0xc638, 0xc638, 0xcdf7, 0xd4f3, 0xbbae, 0xc638, 0xc638, 0xc638, 0xc638, 0xc638, 0x8430, 0x8410,
    0xffff, 0xffff, 0xc638, 0xc638, 0xc638, 0xc638, 0xcd96, 0xdc71, 0xf924, 0xe0c3, 0xa061, 0xc638, 0xc638, 0xc638, 0xc638, 0xc638, 0x8430, 0x8410,
    0xffff, 0xffff, 0xc638, 0xc638, 0xc638, 0xe8a6, 0xf188, 0xfa08, 0xf904, 0xd0a2, 0xa061, 0xc638, 0xc638, 0xc638, 0xc638, 0xc638, 0x8430, 0x8410,
    0xffff, 0xffff, 0xc638, 0xc638, 0xc638, 0xf0c7, 0xf9c8, 0xfa08, 0xf8e3, 0xc8a2, 0xa061, 0xc638, 0xc638, 0xc638, 0xc638, 0xc638, 0x8430, 0x8410,
    0xffff, 0xffff, 0xc638, 0xc638, 0xc638, 0xd493, 0xfa29, 0xf9e7, 0xf0c3, 0xb882, 0xa061, 0xc638, 0xc638, 0xc638, 0xc638, 0xc638, 0x8430, 0x8410,
    0xffff, 0xffff, 0xc638, 0xc638, 0xc638, 0xc638, 0xc638, 0xc638, 0xc638, 0x1841, 0x7861, 0xc638, 0xc638, 0xc638, 0xc638, 0xc638, 0x8430, 0x8410,
    0xffff, 0xffff, 0xc638, 0xc638, 0xc638, 0xc638, 0xc638, 0xc638, 0xc638, 0x5aeb, 0x1861, 0xc638, 0xc638, 0xc638, 0xc638, 0xc638, 0x8430, 0x8410,
    0xffff, 0xffff, 0xc638, 0xc638, 0xc638, 0xc638, 0xc638, 0xc638, 0xc638, 0x5aeb, 0x0861, 0xc638, 0xc638, 0xc638, 0xc638, 0xc638, 0x8430, 0x8410,
    0xffff, 0xffff, 0xc638, 0xc638, 0xc638, 0xc638, 0xc638, 0x630c, 0x0000, 0x0000, 0x0000, 0x7bcf, 0xc638, 0xc638, 0xc638, 0xc638, 0x8430, 0x8410,
    0xffff, 0xffff, 0xc638, 0xc638, 0xc638, 0x94b2, 0x94b2, 0x2124, 0x0000, 0x0000, 0x0000, 0x4a49, 0x94b2, 0x94b2, 0xc638, 0xc638, 0x8430, 0x8410,
    0xffff, 0xffff, 0xc638, 0xc638, 0xc638, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0xc638, 0xc638, 0x8430, 0x8410,
    0xffff, 0xffff, 0xc638, 0xc638, 0xc638, 0x3186, 0x3186, 0x3186, 0x3186, 0x3186, 0x3186, 0x3186, 0x3186, 0x3186, 0xc638, 0xc638, 0x8430, 0x8410,
    0xffff, 0xffff, 0xc638, 0xc638, 0xc638, 0xc638, 0xc638, 0xc638, 0xc638, 0xc638, 0xc638, 0xc638, 0xc638, 0xc638, 0xc638, 0xc638, 0x8430, 0x8410,
    0xffff, 0xffff, 0x8430, 0x8430, 0x8430, 0x8430, 0x8430, 0x8430, 0x8430, 0x8430, 0x8430, 0x8430, 0x8430, 0x8430, 0x8430, 0x8430, 0x8410, 0x8410,
    0xc638, 0x8410, 0x8410, 0x8410, 0x8410, 0x8410, 0x8410, 0x8410, 0x8410, 0x8410, 0x8410, 0x8410, 0x8410, 0x8410, 0x8410, 0x8410, 0x8410, 0x8410

};

//wrong flag
const uint16_t symbol5[324] = {
    0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xc638,
    0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0x8410,
    0xffff, 0xffff, 0xfd14, 0xfd14, 0xfd14, 0xfd14, 0xfd14, 0xfd14, 0xfd14, 0xfd14, 0xfd14, 0xfd14, 0xfd14, 0xfd14, 0xfd14, 0xfd14, 0x8c10, 0x8410,
    0xffff, 0xffff, 0xfd14, 0xfd14, 0xfd14, 0xfd14, 0xfd14, 0xfd14, 0xfcd3, 0xfc10, 0xdb0c, 0xfd14, 0xfd14, 0xfd14, 0xfd14, 0xfd14, 0x8c10, 0x8410,
    0xffff, 0xffff, 0xfd14, 0xfd14, 0xfd14, 0xfd14, 0xfc92, 0xfbcf, 0xf924, 0xe0c3, 0xa061, 0xfd14, 0xfd14, 0xfd14, 0xfd14, 0xfd14, 0x8c10, 0x8410,
    0xffff, 0xffff, 0xfd14, 0xfd14, 0xfd14, 0xe8a6, 0xf188, 0xfa08, 0xf904, 0xd0a2, 0xa061, 0xfd14, 0xfd14, 0xfd14, 0xfd14, 0xfd14, 0x8c10, 0x8410,
    0xffff, 0xffff, 0xfd14, 0xfd14, 0xfd14, 0xf0c7, 0xf9c8, 0xfa08, 0xf8e3, 0xc8a2, 0xa061, 0xfd14, 0xfd14, 0xfd14, 0xfd14, 0xfd14, 0x8c10, 0x8410,
    0xffff, 0xffff, 0xfd14, 0xfd14, 0xfd14, 0xfbd0, 0xfa09, 0xf9e7, 0xf0c3, 0xb882, 0xa061, 0xfd14, 0xfd14, 0xfd14, 0xfd14, 0xfd14, 0x8c10, 0x8410,
    0xffff, 0xffff, 0xfd14, 0xfd14, 0xfd14, 0xfd14, 0xfd14, 0xfd14, 0xfd14, 0x1820, 0x8061, 0xfd14, 0xfd14, 0xfd14, 0xfd14, 0xfd14, 0x8c10, 0x8410,
    0xffff, 0xffff, 0xfd14, 0xfd14, 0xfd14, 0xfd14, 0xfd14, 0xfd14, 0xfd14, 0x7249, 0x1861, 0xfd14, 0xfd14, 0xfd14, 0xfd14, 0xfd14, 0x8c10, 0x8410,
    0xffff, 0xffff, 0xfd14, 0xfd14, 0xfd14, 0xfd14, 0xfd14, 0xfd14, 0xfd14, 0x7249, 0x1061, 0xfd14, 0xfd14, 0xfd14, 0xfd14, 0xfd14, 0x8c10, 0x8410,
    0xffff, 0xffff, 0xfd14, 0xfd14, 0xfd14, 0xfd14, 0xfd14, 0x7a8a, 0x0000, 0x0000, 0x0000, 0x9b2c, 0xfd14, 0xfd14, 0xfd14, 0xfd14, 0x8c10, 0x8410,
    0xffff, 0xffff, 0xfd14, 0xfd14, 0xfd14, 0xc3cf, 0xc3cf, 0x28e3, 0x0000, 0x0000, 0x0000, 0x59e7, 0xc3cf, 0xc3cf, 0xfd14, 0xfd14, 0x8c10, 0x8410,
    0xffff, 0xffff, 0xfd14, 0xfd14, 0xfd14, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0xfd14, 0xfd14, 0x8c10, 0x8410,
    0xffff, 0xffff, 0xfd14, 0xfd14, 0xfd14, 0x3945, 0x3945, 0x3945, 0x3945, 0x3945, 0x3945, 0x3945, 0x3945, 0x3945, 0xfd14, 0xfd14, 0x8c10, 0x8410,
    0xffff, 0xffff, 0xfd14, 0xfd14, 0xfd14, 0xfd14, 0xfd14, 0xfd14, 0xfd14, 0xfd14, 0xfd14, 0xfd14, 0xfd14, 0xfd14, 0xfd14, 0xfd14, 0x8c10, 0x8410,
    0xffff, 0xffff, 0x8c10, 0x8c10, 0x8c10, 0x8c10, 0x8c10, 0x8c10, 0x8c10, 0x8c10, 0x8c10, 0x8c10, 0x8c10, 0x8c10, 0x8c10, 0x8c10, 0x8410, 0x8410,
    0xc638, 0x8410, 0x8410, 0x8410, 0x8410, 0x8410, 0x8410, 0x8410, 0x8410, 0x8410, 0x8410, 0x8410, 0x8410, 0x8410, 0x8410, 0x8410, 0x8410, 0x8410

};

const uint16_t number0[324] = {
    0x8410, 0x8410, 0x8410, 0x8410, 0x8410, 0x8410, 0x8410, 0x8410, 0x8410, 0x8410, 0x8410, 0x8410, 0x8410, 0x8410, 0x8410, 0x8410, 0x8410, 0x8410,
    0xa534, 0xc638, 0xc638, 0xc638, 0xc638, 0xc638, 0xc638, 0xc638, 0xc638, 0xc638, 0xc638, 0xc638, 0xc638, 0xc638, 0xc638, 0xc638, 0xc638, 0x8410,
    0xa534, 0xc638, 0xc638, 0xc638, 0xc638, 0xc638, 0xc638, 0xc638, 0xc638, 0xc638, 0xc638, 0xc638, 0xc638, 0xc638, 0xc638, 0xc638, 0xc638, 0x8410,
    0xa534, 0xc638, 0xc638, 0xc638, 0xc638, 0xc638, 0xc638, 0xc638, 0xc638, 0xc638, 0xc638, 0xc638, 0xc638, 0xc638, 0xc638, 0xc638, 0xc638, 0x8410,
    0xa534, 0xc638, 0xc638, 0xc638, 0xc638, 0xc638, 0xc638, 0xc638, 0xc638, 0xc638, 0xc638, 0xc638, 0xc638, 0xc638, 0xc638, 0xc638, 0xc638, 0x8410,
    0xa534, 0xc638, 0xc638, 0xc638, 0xc638, 0xc638, 0xc638, 0xc638, 0xc638, 0xc638, 0xc638, 0xc638, 0xc638, 0xc638, 0xc638, 0xc638, 0xc638, 0x8410,
    0xa534, 0xc638, 0xc638, 0xc638, 0xc638, 0xc638, 0xc638, 0xc638, 0xc638, 0xc638, 0xc638, 0xc638, 0xc638, 0xc638, 0xc638, 0xc638, 0xc638, 0x8410,
    0xa534, 0xc638, 0xc638, 0xc638, 0xc638, 0xc638, 0xc638, 0xc638, 0xc638, 0xc638, 0xc638, 0xc638, 0xc638, 0xc638, 0xc638, 0xc638, 0xc638, 0x8410,
    0xa534, 0xc638, 0xc638, 0xc638, 0xc638, 0xc638, 0xc638, 0xc638, 0xc638, 0xc638, 0xc638, 0xc638, 0xc638, 0xc638, 0xc638, 0xc638, 0xc638, 0x8410,
    0xa534, 0xc638, 0xc638, 0xc638, 0xc638, 0xc638, 0xc638, 0xc638, 0xc638, 0xc638, 0xc638, 0xc638, 0xc638, 0xc638, 0xc638, 0xc638, 0xc638, 0x8410,
    0xa534, 0xc638, 0xc638, 0xc638, 0xc638, 0xc638, 0xc638, 0xc638, 0xc638, 0xc638, 0xc638, 0xc638, 0xc638, 0xc638, 0xc638, 0xc638, 0xc638, 0x8410,
    0xa534, 0xc638, 0xc638, 0xc638, 0xc638, 0xc638, 0xc638, 0xc638, 0xc638, 0xc638, 0xc638, 0xc638, 0xc638, 0xc638, 0xc638, 0xc638, 0xc638, 0x8410,
    0xa534, 0xc638, 0xc638, 0xc638, 0xc638, 0xc638, 0xc638, 0xc638, 0xc638, 0xc638, 0xc638, 0xc638, 0xc638, 0xc638, 0xc638, 0xc638, 0xc638, 0x8410,
    0xa534, 0xc638, 0xc638, 0xc638, 0xc638, 0xc638, 0xc638, 0xc638, 0xc638, 0xc638, 0xc638, 0xc638, 0xc638, 0xc638, 0xc638, 0xc638, 0xc638, 0x8410,
    0xa534, 0xc638, 0xc638, 0xc638, 0xc638, 0xc638, 0xc638, 0xc638, 0xc638, 0xc638, 0xc638, 0xc638, 0xc638, 0xc638, 0xc638, 0xc638, 0xc638, 0x8410,
    0xa534, 0xc638, 0xc638, 0xc638, 0xc638, 0xc638, 0xc638, 0xc638, 0xc638, 0xc638, 0xc638, 0xc638, 0xc638, 0xc638, 0xc638, 0xc638, 0xc638, 0x8410,
    0xa534, 0xc638, 0xc638, 0xc638, 0xc638, 0xc638, 0xc638, 0xc638, 0xc638, 0xc638, 0xc638, 0xc638, 0xc638, 0xc638, 0xc638, 0xc638, 0xc638, 0x8410,
    0xa534, 0xc638, 0xc638, 0xc638, 0xc638, 0xc638, 0xc638, 0xc638, 0xc638, 0xc638, 0xc638, 0xc638, 0xc638, 0xc638, 0xc638, 0xc638, 0xc638, 0x8410

};
const uint16_t number1[324] = {
    0x8410, 0x8410, 0x8410, 0x8410, 0x8410, 0x8410, 0x8410, 0x8410, 0x8410, 0x8410, 0x8410, 0x8410, 0x8410, 0x8410, 0x8410, 0x8410, 0x8410, 0x8410,
    0x8410, 0x94b2, 0xa534, 0xa534, 0xa534, 0xa534, 0xa534, 0xa534, 0xa534, 0xa534, 0xa534, 0xa534, 0xa534, 0xa534, 0xa534, 0xa534, 0xa534, 0xa534,
    0x8410, 0xa534, 0xc638, 0xc638, 0xc638, 0xc638, 0xc638, 0xc638, 0xc638, 0xc638, 0xc638, 0xc638, 0xc638, 0xc638, 0xc638, 0xc638, 0xc638, 0xc638,
    0x8410, 0xa534, 0xc638, 0xc638, 0xc638, 0xc638, 0xc638, 0xc638, 0xc638, 0xc638, 0xc638, 0xc638, 0xc638, 0xc638, 0xc638, 0xc638, 0xc638, 0xc638,
    0x8410, 0xa534, 0xc638, 0xc638, 0xc638, 0xc638, 0xc638, 0xc638, 0x631c, 0x001f, 0x001f, 0xc638, 0xc638, 0xc638, 0xc638, 0xc638, 0xc638, 0xc638,
    0x8410, 0xa534, 0xc638, 0xc638, 0xc638, 0xc638, 0xc638, 0xc638, 0x001f, 0x001f, 0x001f, 0xc638, 0xc638, 0xc638, 0xc638, 0xc638, 0xc638, 0xc638,
    0x8410, 0xa534, 0xc638, 0xc638, 0xc638, 0xc638, 0xbdd9, 0x39fd, 0x001f, 0x001f, 0x001f, 0xc638, 0xc638, 0xc638, 0xc638, 0xc638, 0xc638, 0xc638,
    0x8410, 0xa534, 0xc638, 0xc638, 0xc638, 0x6b7b, 0x087f, 0x001f, 0x001f, 0x001f, 0x001f, 0xc638, 0xc638, 0xc638, 0xc638, 0xc638, 0xc638, 0xc638,
    0x8410, 0xa534, 0xc638, 0xc638, 0xc638, 0xc638, 0xc638, 0xc638, 0x001f, 0x001f, 0x001f, 0xc638, 0xc638, 0xc638, 0xc638, 0xc638, 0xc638, 0xc638,
    0x8410, 0xa534, 0xc638, 0xc638, 0xc638, 0xc638, 0xc638, 0xc638, 0x001f, 0x001f, 0x001f, 0xc638, 0xc638, 0xc638, 0xc638, 0xc638, 0xc638, 0xc638,
    0x8410, 0xa534, 0xc638, 0xc638, 0xc638, 0xc638, 0xc638, 0xc638, 0x001f, 0x001f, 0x001f, 0xc638, 0xc638, 0xc638, 0xc638, 0xc638, 0xc638, 0xc638,
    0x8410, 0xa534, 0xc638, 0xc638, 0xc638, 0xc638, 0xc638, 0xc638, 0x001f, 0x001f, 0x001f, 0xc638, 0xc638, 0xc638, 0xc638, 0xc638, 0xc638, 0xc638,
    0x8410, 0xa534, 0xc638, 0xc638, 0xc638, 0xc638, 0xc638, 0xc638, 0x001f, 0x001f, 0x001f, 0xc638, 0xc638, 0xc638, 0xc638, 0xc638, 0xc638, 0xc638,
    0x8410, 0xa534, 0xc638, 0xc638, 0xc638, 0x319e, 0x001f, 0x001f, 0x001f, 0x001f, 0x001f, 0x001f, 0x001f, 0x319e, 0xc638, 0xc638, 0xc638, 0xc638,
    0x8410, 0xa534, 0xc638, 0xc638, 0xc638, 0x319e, 0x001f, 0x001f, 0x001f, 0x001f, 0x001f, 0x001f, 0x001f, 0x319e, 0xc638, 0xc638, 0xc638, 0xc638,
    0x8410, 0xa534, 0xc638, 0xc638, 0xc638, 0xc638, 0xc638, 0xc638, 0xc638, 0xc638, 0xc638, 0xc638, 0xc638, 0xc638, 0xc638, 0xc638, 0xc638, 0xc638,
    0x8410, 0xa534, 0xc638, 0xc638, 0xc638, 0xc638, 0xc638, 0xc638, 0xc638, 0xc638, 0xc638, 0xc638, 0xc638, 0xc638, 0xc638, 0xc638, 0xc638, 0xc638,
    0x8410, 0xa534, 0xc638, 0xc638, 0xc638, 0xc638, 0xc638, 0xc638, 0xc638, 0xc638, 0xc638, 0xc638, 0xc638, 0xc638, 0xc638, 0xc638, 0xc638, 0xc638

};
const uint16_t number2[324] = {
    0x8410, 0x8410, 0x8410, 0x8410, 0x8410, 0x8410, 0x8410, 0x8410, 0x8410, 0x8410, 0x8410, 0x8410, 0x8410, 0x8410, 0x8410, 0x8410, 0x8410, 0x8410,
    0x8410, 0x94b2, 0xa534, 0xa534, 0xa534, 0xa534, 0xa534, 0xa534, 0xa534, 0xa534, 0xa534, 0xa534, 0xa534, 0xa534, 0xa534, 0xa534, 0xa534, 0xa534,
    0x8410, 0xa534, 0xc638, 0xc638, 0xc638, 0xc638, 0xc638, 0xc638, 0xc638, 0xc638, 0xc638, 0xc638, 0xc638, 0xc638, 0xc638, 0xc638, 0xc638, 0xc638,
    0x8410, 0xa534, 0xc638, 0xc638, 0xc638, 0xc638, 0xc638, 0xc638, 0xc638, 0xc638, 0xc638, 0xc638, 0xc638, 0xc638, 0xc638, 0xc638, 0xc638, 0xc638,
    0x8410, 0xa534, 0xc638, 0xc638, 0xa5d4, 0x0400, 0x0400, 0x0400, 0x0400, 0x0400, 0x0400, 0x0400, 0x0400, 0x0400, 0x54ea, 0xc638, 0xc638, 0xc638,
    0x8410, 0xa534, 0xc638, 0xc638, 0x3486, 0x0400, 0x0400, 0x0400, 0x0400, 0x0400, 0x0400, 0x0400, 0x0400, 0x0400, 0x0400, 0x95b2, 0xc638, 0xc638,
    0x8410, 0xa534, 0xc638, 0xc638, 0x3486, 0x0400, 0x0400, 0x3486, 0xc638, 0xc638, 0xc638, 0xadf5, 0x1c43, 0x0400, 0x0400, 0x95b2, 0xc638, 0xc638,
    0x8410, 0xa534, 0xc638, 0xc638, 0x7d4f, 0x650c, 0x650c, 0x7d4f, 0xc638, 0xc638, 0xc638, 0xc638, 0x3486, 0x0400, 0x0400, 0x95b2, 0xc638, 0xc638,
    0x8410, 0xa534, 0xc638, 0xc638, 0xc638, 0xc638, 0xc638, 0xc638, 0xadf5, 0x754e, 0x3486, 0x0400, 0x0400, 0x0400, 0x0c21, 0xc638, 0xc638, 0xc638,
    0x8410, 0xa534, 0xc638, 0xc638, 0xc638, 0xc638, 0xadf5, 0x754e, 0x0400, 0x0400, 0x0400, 0x0400, 0x0400, 0x0400, 0x8d91, 0xc638, 0xc638, 0xc638,
    0x8410, 0xa534, 0xc638, 0xc638, 0xc638, 0x3486, 0x0400, 0x0400, 0x0400, 0x0400, 0x0400, 0x1c43, 0x54ea, 0xa5d4, 0xc638, 0xc638, 0xc638, 0xc638,
    0x8410, 0xa534, 0xc638, 0xc638, 0x3486, 0x0400, 0x0400, 0x0400, 0xa5d4, 0xc638, 0xc638, 0xc638, 0xc638, 0xc638, 0xc638, 0xc638, 0xc638, 0xc638,
    0x8410, 0xa534, 0xc638, 0xc638, 0x3486, 0x0400, 0x0400, 0x3486, 0xc638, 0xc638, 0xc638, 0xc638, 0xc638, 0xc638, 0xc638, 0xc638, 0xc638, 0xc638,
    0x8410, 0xa534, 0xc638, 0xc638, 0x3486, 0x0400, 0x0400, 0x0400, 0x0400, 0x0400, 0x0400, 0x0400, 0x0400, 0x0400, 0x0400, 0xa5d4, 0xc638, 0xc638,
    0x8410, 0xa534, 0xc638, 0xc638, 0x3486, 0x0400, 0x0400, 0x0400, 0x0400, 0x0400, 0x0400, 0x0400, 0x0400, 0x0400, 0x0400, 0x95b2, 0xc638, 0xc638,
    0x8410, 0xa534, 0xc638, 0xc638, 0xc638, 0xc638, 0xc638, 0xc638, 0xc638, 0xc638, 0xc638, 0xc638, 0xc638, 0xc638, 0xc638, 0xc638, 0xc638, 0xc638,
    0x8410, 0xa534, 0xc638, 0xc638, 0xc638, 0xc638, 0xc638, 0xc638, 0xc638, 0xc638, 0xc638, 0xc638, 0xc638, 0xc638, 0xc638, 0xc638, 0xc638, 0xc638,
    0x8410, 0xa534, 0xc638, 0xc638, 0xc638, 0xc638, 0xc638, 0xc638, 0xc638, 0xc638, 0xc638, 0xc638, 0xc638, 0xc638, 0xc638, 0xc638, 0xc638, 0xc638

};
const uint16_t number3[324] = {
    0x8410, 0x8410, 0x8410, 0x8410, 0x8410, 0x8410, 0x8410, 0x8410, 0x8410, 0x8410, 0x8410, 0x8410, 0x8410, 0x8410, 0x8410, 0x8410, 0x8410, 0x8410,
    0x8410, 0x94b2, 0xa534, 0xa534, 0xa534, 0xa534, 0xa534, 0xa534, 0xa534, 0xa534, 0xa534, 0xa534, 0xa534, 0xa534, 0xa534, 0xa534, 0xa534, 0xa534,
    0x8410, 0xa534, 0xc638, 0xc638, 0xc638, 0xc638, 0xc638, 0xc638, 0xc638, 0xc638, 0xc638, 0xc638, 0xc638, 0xc638, 0xc638, 0xc638, 0xc638, 0xc638,
    0x8410, 0xa534, 0xc638, 0xc638, 0xc638, 0xc638, 0xc638, 0xc638, 0xc638, 0xc638, 0xc638, 0xc638, 0xc638, 0xc638, 0xc638, 0xc638, 0xc638, 0xc638,
    0x8410, 0xa534, 0xc638, 0xc638, 0xe9e7, 0xf800, 0xf800, 0xf800, 0xf800, 0xf800, 0xf800, 0xf800, 0xf800, 0xf800, 0xdbcf, 0xc638, 0xc638, 0xc638,
    0x8410, 0xa534, 0xc638, 0xc638, 0xf186, 0xf800, 0xf800, 0xf800, 0xf800, 0xf800, 0xf800, 0xf800, 0xf800, 0xf800, 0xf800, 0xd4b2, 0xc638, 0xc638,
    0x8410, 0xa534, 0xc638, 0xc638, 0xc638, 0xc638, 0xc638, 0xc638, 0xc638, 0xc638, 0xc638, 0xdc51, 0xf800, 0xf800, 0xf800, 0xd4b2, 0xc638, 0xc638,
    0x8410, 0xa534, 0xc638, 0xc638, 0xc638, 0xc638, 0xc638, 0xc638, 0xc638, 0xc638, 0xc638, 0xd4b2, 0xf800, 0xf800, 0xf800, 0xd4b2, 0xc638, 0xc638,
    0x8410, 0xa534, 0xc638, 0xc638, 0xc638, 0xc638, 0xc638, 0xd4b2, 0xf800, 0xf800, 0xf800, 0xf800, 0xf800, 0xf800, 0xcd75, 0xc638, 0xc638, 0xc638,
    0x8410, 0xa534, 0xc638, 0xc638, 0xc638, 0xc638, 0xc638, 0xd4b2, 0xf800, 0xf800, 0xf800, 0xf800, 0xf800, 0xf800, 0xc638, 0xc638, 0xc638, 0xc638,
    0x8410, 0xa534, 0xc638, 0xc638, 0xc638, 0xc638, 0xc638, 0xd4b2, 0xf800, 0xf800, 0xf800, 0xf800, 0xf800, 0xf800, 0xcdd7, 0xc638, 0xc638, 0xc638,
    0x8410, 0xa534, 0xc638, 0xc638, 0xc638, 0xc638, 0xc638, 0xc638, 0xc638, 0xc638, 0xc638, 0xd4b2, 0xf800, 0xf800, 0xf800, 0xd4b2, 0xc638, 0xc638,
    0x8410, 0xa534, 0xc638, 0xc638, 0xc638, 0xc638, 0xc638, 0xc638, 0xc638, 0xc638, 0xc638, 0xdc51, 0xf800, 0xf800, 0xf800, 0xd4b2, 0xc638, 0xc638,
    0x8410, 0xa534, 0xc638, 0xc638, 0xf186, 0xf800, 0xf800, 0xf800, 0xf800, 0xf800, 0xf800, 0xf800, 0xf800, 0xf800, 0xf800, 0xd4b2, 0xc638, 0xc638,
    0x8410, 0xa534, 0xc638, 0xc638, 0xe2aa, 0xf800, 0xf800, 0xf800, 0xf800, 0xf800, 0xf800, 0xf800, 0xf800, 0xf800, 0xdc51, 0xc638, 0xc638, 0xc638,
    0x8410, 0xa534, 0xc638, 0xc638, 0xc638, 0xc638, 0xc638, 0xc638, 0xc638, 0xc638, 0xc638, 0xc638, 0xc638, 0xc638, 0xc638, 0xc638, 0xc638, 0xc638,
    0x8410, 0xa534, 0xc638, 0xc638, 0xc638, 0xc638, 0xc638, 0xc638, 0xc638, 0xc638, 0xc638, 0xc638, 0xc638, 0xc638, 0xc638, 0xc638, 0xc638, 0xc638,
    0x8410, 0xa534, 0xc638, 0xc638, 0xc638, 0xc638, 0xc638, 0xc638, 0xc638, 0xc638, 0xc638, 0xc638, 0xc638, 0xc638, 0xc638, 0xc638, 0xc638, 0xc638

};
const uint16_t number4[324] = {
    0x8410, 0x8410, 0x8410, 0x8410, 0x8410, 0x8410, 0x8410, 0x8410, 0x8410, 0x8410, 0x8410, 0x8410, 0x8410, 0x8410, 0x8410, 0x8410, 0x8410, 0x8410,
    0x8410, 0x94b2, 0xa534, 0xa534, 0xa534, 0xa534, 0xa534, 0xa534, 0xa534, 0xa534, 0xa534, 0xa534, 0xa534, 0xa534, 0xa534, 0xa534, 0xa534, 0xa534,
    0x8410, 0xa534, 0xc638, 0xc638, 0xc638, 0xc638, 0xc638, 0xc638, 0xc638, 0xc638, 0xc638, 0xc638, 0xc638, 0xc638, 0xc638, 0xc638, 0xc638, 0xc638,
    0x8410, 0xa534, 0xc638, 0xc638, 0xc638, 0xc638, 0xc638, 0xc638, 0xc638, 0xc638, 0xc638, 0xc638, 0xc638, 0xc638, 0xc638, 0xc638, 0xc638, 0xc638,
    0x8410, 0xa534, 0xc638, 0xc638, 0xc638, 0xc638, 0x52b3, 0x0010, 0x0010, 0x7bd5, 0xc638, 0x0010, 0x0010, 0x0010, 0xc638, 0xc638, 0xc638, 0xc638,
    0x8410, 0xa534, 0xc638, 0xc638, 0xc638, 0x39f2, 0x0010, 0x0010, 0x52b3, 0xc638, 0xc638, 0x0010, 0x0010, 0x0010, 0xc638, 0xc638, 0xc638, 0xc638,
    0x8410, 0xa534, 0xc638, 0xc638, 0xc638, 0x0010, 0x0010, 0x0010, 0xad77, 0xc638, 0xc638, 0x0010, 0x0010, 0x0010, 0xc638, 0xc638, 0xc638, 0xc638,
    0x8410, 0xa534, 0xc638, 0xc638, 0xc638, 0x0010, 0x0010, 0x0010, 0xc638, 0xc638, 0xc638, 0x0010, 0x0010, 0x0010, 0xc638, 0xc638, 0xc638, 0xc638,
    0x8410, 0xa534, 0xc638, 0xc638, 0x7bd5, 0x0010, 0x0010, 0x0010, 0x0010, 0x0010, 0x0010, 0x0010, 0x0010, 0x0010, 0x0870, 0xad77, 0xc638, 0xc638,
    0x8410, 0xa534, 0xc638, 0xc638, 0x3192, 0x0010, 0x0010, 0x0010, 0x0010, 0x0010, 0x0010, 0x0010, 0x0010, 0x0010, 0x0010, 0x94b6, 0xc638, 0xc638,
    0x8410, 0xa534, 0xc638, 0xc638, 0x2131, 0x0010, 0x0010, 0x0010, 0x0010, 0x0010, 0x0010, 0x0010, 0x0010, 0x0010, 0x0010, 0xa517, 0xc638, 0xc638,
    0x8410, 0xa534, 0xc638, 0xc638, 0xc638, 0xc638, 0xc638, 0xc638, 0xc638, 0xc638, 0xc638, 0x0010, 0x0010, 0x0010, 0xc638, 0xc638, 0xc638, 0xc638,
    0x8410, 0xa534, 0xc638, 0xc638, 0xc638, 0xc638, 0xc638, 0xc638, 0xc638, 0xc638, 0xc638, 0x0010, 0x0010, 0x0010, 0xc638, 0xc638, 0xc638, 0xc638,
    0x8410, 0xa534, 0xc638, 0xc638, 0xc638, 0xc638, 0xc638, 0xc638, 0xc638, 0xc638, 0xc638, 0x0010, 0x0010, 0x0010, 0xc638, 0xc638, 0xc638, 0xc638,
    0x8410, 0xa534, 0xc638, 0xc638, 0xc638, 0xc638, 0xc638, 0xc638, 0xc638, 0xc638, 0xc638, 0x0010, 0x0010, 0x0010, 0xc638, 0xc638, 0xc638, 0xc638,
    0x8410, 0xa534, 0xc638, 0xc638, 0xc638, 0xc638, 0xc638, 0xc638, 0xc638, 0xc638, 0xc638, 0xc638, 0xc638, 0xc638, 0xc638, 0xc638, 0xc638, 0xc638,
    0x8410, 0xa534, 0xc638, 0xc638, 0xc638, 0xc638, 0xc638, 0xc638, 0xc638, 0xc638, 0xc638, 0xc638, 0xc638, 0xc638, 0xc638, 0xc638, 0xc638, 0xc638,
    0x8410, 0xa534, 0xc638, 0xc638, 0xc638, 0xc638, 0xc638, 0xc638, 0xc638, 0xc638, 0xc638, 0xc638, 0xc638, 0xc638, 0xc638, 0xc638, 0xc638, 0xc638

};
const uint16_t number5[324] = {
    0x8410, 0x8410, 0x8410, 0x8410, 0x8410, 0x8410, 0x8410, 0x8410, 0x8410, 0x8410, 0x8410, 0x8410, 0x8410, 0x8410, 0x8410, 0x8410, 0x8410, 0x8410,
    0x8410, 0x94b2, 0xa534, 0xa534, 0xa534, 0xa534, 0xa534, 0xa534, 0xa534, 0xa534, 0xa534, 0xa534, 0xa534, 0xa534, 0xa534, 0xa534, 0xa534, 0xa534,
    0x8410, 0xa534, 0xc638, 0xc638, 0xc638, 0xc638, 0xc638, 0xc638, 0xc638, 0xc638, 0xc638, 0xc638, 0xc638, 0xc638, 0xc638, 0xc638, 0xc638, 0xc638,
    0x8410, 0xa534, 0xc638, 0xc638, 0xc638, 0xc638, 0xc638, 0xc638, 0xc638, 0xc638, 0xc638, 0xc638, 0xc638, 0xc638, 0xc638, 0xc638, 0xc638, 0xc638,
    0x8410, 0xa534, 0xc638, 0xc638, 0x9186, 0x8000, 0x8000, 0x8000, 0x8000, 0x8000, 0x8000, 0x8000, 0x8000, 0x8000, 0x8000, 0xb4b2, 0xc638, 0xc638,
    0x8410, 0xa534, 0xc638, 0xc638, 0x9186, 0x8000, 0x8000, 0x8000, 0x8000, 0x8000, 0x8000, 0x8000, 0x8000, 0x8000, 0x91e7, 0xc638, 0xc638, 0xc638,
    0x8410, 0xa534, 0xc638, 0xc638, 0x9186, 0x8000, 0x8000, 0x9186, 0xc638, 0xc638, 0xc638, 0xc638, 0xc638, 0xc638, 0xc638, 0xc638, 0xc638, 0xc638,
    0x8410, 0xa534, 0xc638, 0xc638, 0x9186, 0x8000, 0x8000, 0x9186, 0xc638, 0xc638, 0xc638, 0xc638, 0xc638, 0xc638, 0xc638, 0xc638, 0xc638, 0xc638,
    0x8410, 0xa534, 0xc638, 0xc638, 0x9186, 0x8000, 0x8000, 0x8000, 0x8000, 0x8000, 0x8000, 0x8000, 0x8000, 0x8000, 0x9186, 0xc638, 0xc638, 0xc638,
    0x8410, 0xa534, 0xc638, 0xc638, 0x9186, 0x8000, 0x8000, 0x8000, 0x8000, 0x8000, 0x8000, 0x8000, 0x8000, 0x8000, 0x8000, 0xb4b2, 0xc638, 0xc638,
    0x8410, 0xa534, 0xc638, 0xc638, 0x9186, 0x8000, 0x8000, 0x8000, 0x8000, 0x8000, 0x8000, 0x8000, 0x8000, 0x8000, 0x8000, 0xb4b2, 0xc638, 0xc638,
    0x8410, 0xa534, 0xc638, 0xc638, 0xc638, 0xc638, 0xc638, 0xc638, 0xc638, 0xc638, 0xc638, 0xb4b2, 0x8000, 0x8000, 0x8000, 0xb4b2, 0xc638, 0xc638,
    0x8410, 0xa534, 0xc638, 0xc638, 0xc638, 0xc638, 0xc638, 0xc638, 0xc638, 0xc638, 0xc638, 0xa36d, 0x8000, 0x8000, 0x8000, 0xb4b2, 0xc638, 0xc638,
    0x8410, 0xa534, 0xc638, 0xc638, 0x9186, 0x8000, 0x8000, 0x8000, 0x8000, 0x8000, 0x8000, 0x8000, 0x8000, 0x8000, 0x8000, 0xb4b2, 0xc638, 0xc638,
    0x8410, 0xa534, 0xc638, 0xc638, 0xa30c, 0x8000, 0x8000, 0x8000, 0x8000, 0x8000, 0x8000, 0x8000, 0x8000, 0x8061, 0x9aaa, 0xc638, 0xc638, 0xc638,
    0x8410, 0xa534, 0xc638, 0xc638, 0xc638, 0xc638, 0xc638, 0xc638, 0xc638, 0xc638, 0xc638, 0xc638, 0xc638, 0xc638, 0xc638, 0xc638, 0xc638, 0xc638,
    0x8410, 0xa534, 0xc638, 0xc638, 0xc638, 0xc638, 0xc638, 0xc638, 0xc638, 0xc638, 0xc638, 0xc638, 0xc638, 0xc638, 0xc638, 0xc638, 0xc638, 0xc638,
    0x8410, 0xa534, 0xc638, 0xc638, 0xc638, 0xc638, 0xc638, 0xc638, 0xc638, 0xc638, 0xc638, 0xc638, 0xc638, 0xc638, 0xc638, 0xc638, 0xc638, 0xc638

};

bool win = false;

// Use hardware SPI 240 x 320 pixel
Adafruit_ILI9341 tft = Adafruit_ILI9341(_cs, _dc, _rst);

enum fieldValues : byte
{
  OPEN,
  CLOSED = 10,
  MINE,
  UNKNOWN,
  FLAG,
  ERR
};

class fieldData
{
public:
  fieldData() : value(CLOSED), open(false) {}
  byte value;
  bool open, mine;
};

class game
{
public:
  game(int x, int y)
  {
    go = false;
    wid = x;
    hei = y;
    field = new fieldData[x * y];
    memset(field, 0, x * y * sizeof(fieldData));
    oMines = ((22 - random(11)) * x * y) / 100;
    mMines = 0;
    int mx, my, m = 0;
    for (; m < oMines; m++)
    {
      do
      {
        mx = random(wid);
        my = random(hei);
      } while (field[mx + wid * my].mine);
      field[mx + wid * my].mine = true;
    }
    remainingMine();
  }

  void makeMove(int x, int y, String a)
  {
    fieldData *fd = &field[wid * y + x];
    if (fd->open && fd->value < CLOSED)
    {
      Serial.print("This cell is already open!");
      return;
    }

    if (a[0] == 'O') {
      if (field[x + y * wid].value == UNKNOWN)
      {
        field[x + y * wid].value = CLOSED;
        field[x + y * wid].open = false;
      } 
      openCell(x, y);
    }
    else if (a[0] == 'F')
    {
      if (field[x + y * wid].value == FLAG) {
        fd->open = false;
        fd->value = CLOSED;
        field[x + y * wid].value = CLOSED;
        field[x + y * wid].open = false;
        mMines--;
        remainingMine();
      } else {
        fd->open = true;
        fd->value = FLAG;
        mMines++;
        remainingMine();
        checkWin();
      }
    }
    else
    {
      fd->open = true;
      fd->value = UNKNOWN;
      if (field[x + y * wid].value == FLAG)
      {
        // field[x + y * wid].value = CLOSED;
        // field[x + y * wid].open = false;
        mMines--;
        remainingMine();
      } 
    }
  }

  void drawBoard()
  {
    // Serial.printf("\nMarked mines: %d from %d\n\n", mMines, oMines);
    int yy;
    for (int y = 0; y < hei; y++)
    {
      yy = y * wid;
      fieldData *fd;
      for (int x = 0; x < wid; x++)
      {
        fd = &field[x + yy];
        if (!fd->open)
        {
          // Serial.printf("%c ", graphs[1]);
          tft.drawRGBBitmap(zeroX + (x * boxSize), zeroY + (y * boxSize), symbol1, boxSize, boxSize);
        }
        else
        {
          if (fd->value > 9)
          {

            switch ((fd->value) - 9)
            {
            case 2:
              tft.drawRGBBitmap(zeroX + (x * boxSize), zeroY + (y * boxSize), symbol2, boxSize, boxSize);
              break;
            case 3:
              tft.drawRGBBitmap(zeroX + (x * boxSize), zeroY + (y * boxSize), symbol3, boxSize, boxSize);
              break;
            case 4:
              tft.drawRGBBitmap(zeroX + (x * boxSize), zeroY + (y * boxSize), symbol4, boxSize, boxSize);
              break;
            case 5:
              tft.drawRGBBitmap(zeroX + (x * boxSize), zeroY + (y * boxSize), symbol5, boxSize, boxSize);
              break;
            }
          }
          else
          {
            if (fd->value < 1)
            {
              tft.drawRGBBitmap(zeroX + (x * boxSize), zeroY + (y * boxSize), number0, boxSize, boxSize);
              if (x == 15 && y == 8)
              {
                tft.drawRGBBitmap(zeroX + (15 * boxSize), zeroY + (0 * boxSize), symbol3, boxSize, boxSize);
              }
            }

            else
            {
              if (x == 15 && y == 8)
              {
                tft.drawRGBBitmap(zeroX + (15 * boxSize), zeroY + (0 * boxSize), symbol3, boxSize, boxSize);
              }

              switch (fd->value)
              {
              case 1:
                tft.drawRGBBitmap(zeroX + (x * boxSize), zeroY + (y * boxSize), number1, boxSize, boxSize);

                break;
              case 2:
                tft.drawRGBBitmap(zeroX + (x * boxSize), zeroY + (y * boxSize), number2, boxSize, boxSize);
                break;
              case 3:
                tft.drawRGBBitmap(zeroX + (x * boxSize), zeroY + (y * boxSize), number3, boxSize, boxSize);
                break;
              case 4:
                tft.drawRGBBitmap(zeroX + (x * boxSize), zeroY + (y * boxSize), number4, boxSize, boxSize);
                break;
              case 5:
                tft.drawRGBBitmap(zeroX + (x * boxSize), zeroY + (y * boxSize), number5, boxSize, boxSize);
                break;
              }
            }
          }
        }
      }
    }
    remainingMine();
  }

  void remainingMine()
  {
    int m = oMines - mMines;
    if (m < 0)
      m = 0;
    draw7Number(m, 22, 21, 1, ILI9341_RED, ILI9341_BLACK, 3);
  }
  bool go;

private:
  bool openCell(int x, int y)
  {
    if (!isInside(x, y))
      return false;
    if (field[x + y * wid].mine)
      boom();
    else
    {
      if (field[x + y * wid].value == FLAG)
      {
        field[x + y * wid].value = CLOSED;
        field[x + y * wid].open = false;
        mMines--;
        remainingMine();
      }
      recOpen(x, y);
      checkWin();
    }
    return true;
  }

  void checkWin()
  {
    int z = wid * hei - oMines, yy;
    fieldData *fd;
    for (int y = 0; y < hei; y++)
    {
      yy = wid * y;
      for (int x = 0; x < wid; x++)
      {
        fd = &field[x + yy];
        if (fd->open && fd->value != FLAG)
          z--;
      }
    }
    // Serial.printf("\nz: %d\n", z);
    if (!z)
    {
      lastMsg("Congratulations, you won the game!");
      win = true;
    }
  }

  void boom()
  {
    int yy;
    fieldData *fd;
    for (int y = 0; y < hei; y++)
    {
      yy = wid * y;
      for (int x = 0; x < wid; x++)
      {
        fd = &field[x + yy];
        if (fd->value == FLAG)
        {
          fd->open = true;
          fd->value = fd->mine ? MINE : ERR;
        }
        else if (fd->mine)
        {
          fd->open = true;
          fd->value = MINE;
        }
      }
    }
    lastMsg("B O O O M M M M M !");
    win = false;
  }

  void lastMsg(String s)
  {
    go = true;
    drawBoard();
    Serial.print(s);
    Serial.print("\n\n");
  }

  bool isInside(int x, int y) { return (x > -1 && y > -1 && x < wid && y < hei); }

  void recOpen(int x, int y)
  {
    if (!isInside(x, y) || field[x + y * wid].open)
      return;
    int bc = getMineCount(x, y);
    field[x + y * wid].open = true;
    field[x + y * wid].value = bc;
    if (bc)
      return;

    for (int yy = -1; yy < 2; yy++)
      for (int xx = -1; xx < 2; xx++)
      {
        if (xx == 0 && yy == 0)
          continue;
        recOpen(x + xx, y + yy);
      }
  }

  int getMineCount(int x, int y)
  {
    int m = 0;
    for (int yy = -1; yy < 2; yy++)
      for (int xx = -1; xx < 2; xx++)
      {
        if (xx == 0 && yy == 0)
          continue;
        if (isInside(x + xx, y + yy) && field[x + xx + (y + yy) * wid].mine)
          m++;
      }

    return m;
  }

  void draw7Number(int n, unsigned int xLoc, unsigned int yLoc, char cS, unsigned int fC, unsigned int bC, char nD)
  {
    unsigned int num = abs(n), i, s, t, w, col, h, a, b, si = 0, j = 1, d = 0, S1 = cS, S2 = 5 * cS, S3 = 2 * cS, S4 = 7 * cS, x1 = (S3 / 2) + 1, x2 = (2 * S1) + S2 + 1, y1 = yLoc + x1, y3 = yLoc + (2 * S1) + S4 + 1;
    unsigned int seg[7][3] = {{(S3 / 2) + 1, yLoc, 1}, {x2, y1, 0}, {x2, y3 + x1, 0}, {x1, (2 * y3) - yLoc, 1}, {0, y3 + x1, 0}, {0, y1, 0}, {x1, y3, 1}};
    unsigned char nums[12] = {0x3F, 0x06, 0x5B, 0x4F, 0x66, 0x6D, 0x7D, 0x07, 0x7F, 0x67, 0x00, 0x40}, c = (c = abs(cS)) > 10 ? 10 : (c < 1) ? 1
                                                                                                                                             : c,
                  cnt = (cnt = abs(nD)) > 10 ? 10 : (cnt < 1) ? 1
                                                              : cnt;
    for (xLoc += cnt * (d = (2 * S1) + S2 + (2 * S3) + 2); cnt > 0; cnt--)
    {
      for (i = (num > 9) ? num % 10 : ((!cnt) && (n < 0)) ? 11
                                  : ((nD < 0) && (!num))  ? 10
                                                          : num,
          xLoc -= d, num /= 10, j = 0;
           j < 7; ++j)
      {
        col = (nums[i] & (1 << j)) ? fC : bC;
        s = (2 * S1) / S3;
        if (seg[j][2])
          for (w = S2, t = seg[j][1] + S3, h = seg[j][1] + (S3 / 2), a = xLoc + seg[j][0] + S1, b = seg[j][1]; b < h; b++, a -= s, w += (2 * s))
            tft.drawFastHLine(a, b, w, col);
        else
          for (w = S4, t = xLoc + seg[j][0] + S3, h = xLoc + seg[j][0] + S3 / 2, b = xLoc + seg[j][0], a = seg[j][1] + S1; b < h; b++, a -= s, w += (2 * s))
            tft.drawFastVLine(b, a, w, col);
        for (; b < t; b++, a += s, w -= (2 * s))
          seg[j][2] ? tft.drawFastHLine(a, b, w, col) : tft.drawFastVLine(b, a, w, col);
      }
    }
  }

  int wid, hei, mMines, oMines;
  fieldData *field;
};
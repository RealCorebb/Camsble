// Created by http://oleddisplay.squix.ch/ Consider a donation
// In case of problems make sure that you are using the font file with the correct version!
const uint8_t Open_Sans_Regular_8[] PROGMEM = {
	0x07, // Width: 7
	0x0C, // Height: 12
	0x20, // First Char: 32
	0xE0, // Numbers of Chars: 224

	// Jump Table:
	0xFF, 0xFF, 0x00, 0x02,  // 32:65535
	0x00, 0x00, 0x04, 0x02,  // 33:0
	0x00, 0x04, 0x05, 0x03,  // 34:4
	0x00, 0x09, 0x07, 0x05,  // 35:9
	0x00, 0x10, 0x07, 0x05,  // 36:16
	0x00, 0x17, 0x0C, 0x07,  // 37:23
	0x00, 0x23, 0x0A, 0x06,  // 38:35
	0x00, 0x2D, 0x01, 0x02,  // 39:45
	0x00, 0x2E, 0x04, 0x02,  // 40:46
	0x00, 0x32, 0x04, 0x02,  // 41:50
	0x00, 0x36, 0x07, 0x04,  // 42:54
	0x00, 0x3D, 0x07, 0x05,  // 43:61
	0x00, 0x44, 0x02, 0x02,  // 44:68
	0x00, 0x46, 0x03, 0x03,  // 45:70
	0x00, 0x49, 0x04, 0x02,  // 46:73
	0x00, 0x4D, 0x05, 0x03,  // 47:77
	0x00, 0x52, 0x08, 0x05,  // 48:82
	0x00, 0x5A, 0x06, 0x05,  // 49:90
	0x00, 0x60, 0x08, 0x05,  // 50:96
	0x00, 0x68, 0x08, 0x05,  // 51:104
	0x00, 0x70, 0x08, 0x05,  // 52:112
	0x00, 0x78, 0x08, 0x05,  // 53:120
	0x00, 0x80, 0x08, 0x05,  // 54:128
	0x00, 0x88, 0x07, 0x05,  // 55:136
	0x00, 0x8F, 0x08, 0x05,  // 56:143
	0x00, 0x97, 0x07, 0x05,  // 57:151
	0x00, 0x9E, 0x04, 0x02,  // 58:158
	0x00, 0xA2, 0x02, 0x02,  // 59:162
	0x00, 0xA4, 0x07, 0x05,  // 60:164
	0x00, 0xAB, 0x07, 0x05,  // 61:171
	0x00, 0xB2, 0x07, 0x05,  // 62:178
	0x00, 0xB9, 0x05, 0x03,  // 63:185
	0x00, 0xBE, 0x0D, 0x07,  // 64:190
	0x00, 0xCB, 0x0A, 0x05,  // 65:203
	0x00, 0xD5, 0x09, 0x05,  // 66:213
	0x00, 0xDE, 0x0A, 0x05,  // 67:222
	0x00, 0xE8, 0x09, 0x06,  // 68:232
	0x00, 0xF1, 0x08, 0x04,  // 69:241
	0x00, 0xF9, 0x07, 0x04,  // 70:249
	0x01, 0x00, 0x0A, 0x06,  // 71:256
	0x01, 0x0A, 0x0A, 0x06,  // 72:266
	0x01, 0x14, 0x04, 0x02,  // 73:276
	0x01, 0x18, 0x02, 0x02,  // 74:280
	0x01, 0x1A, 0x0A, 0x05,  // 75:282
	0x01, 0x24, 0x08, 0x04,  // 76:292
	0x01, 0x2C, 0x0C, 0x07,  // 77:300
	0x01, 0x38, 0x0A, 0x06,  // 78:312
	0x01, 0x42, 0x0B, 0x06,  // 79:322
	0x01, 0x4D, 0x07, 0x05,  // 80:333
	0x01, 0x54, 0x0B, 0x06,  // 81:340
	0x01, 0x5F, 0x0A, 0x05,  // 82:351
	0x01, 0x69, 0x08, 0x04,  // 83:361
	0x01, 0x71, 0x07, 0x04,  // 84:369
	0x01, 0x78, 0x0A, 0x06,  // 85:376
	0x01, 0x82, 0x09, 0x05,  // 86:386
	0x01, 0x8B, 0x0D, 0x07,  // 87:395
	0x01, 0x98, 0x08, 0x05,  // 88:408
	0x01, 0xA0, 0x07, 0x04,  // 89:416
	0x01, 0xA7, 0x08, 0x05,  // 90:423
	0x01, 0xAF, 0x04, 0x03,  // 91:431
	0x01, 0xB3, 0x06, 0x03,  // 92:435
	0x01, 0xB9, 0x04, 0x03,  // 93:441
	0x01, 0xBD, 0x07, 0x04,  // 94:445
	0x01, 0xC4, 0x06, 0x04,  // 95:452
	0x01, 0xCA, 0x05, 0x05,  // 96:458
	0x01, 0xCF, 0x08, 0x04,  // 97:463
	0x01, 0xD7, 0x08, 0x05,  // 98:471
	0x01, 0xDF, 0x06, 0x04,  // 99:479
	0x01, 0xE5, 0x08, 0x05,  // 100:485
	0x01, 0xED, 0x08, 0x04,  // 101:493
	0x01, 0xF5, 0x05, 0x03,  // 102:501
	0x01, 0xFA, 0x08, 0x04,  // 103:506
	0x02, 0x02, 0x08, 0x05,  // 104:514
	0x02, 0x0A, 0x04, 0x02,  // 105:522
	0x02, 0x0E, 0x02, 0x02,  // 106:526
	0x02, 0x10, 0x08, 0x04,  // 107:528
	0x02, 0x18, 0x04, 0x02,  // 108:536
	0x02, 0x1C, 0x0E, 0x07,  // 109:540
	0x02, 0x2A, 0x08, 0x05,  // 110:554
	0x02, 0x32, 0x08, 0x05,  // 111:562
	0x02, 0x3A, 0x08, 0x05,  // 112:570
	0x02, 0x42, 0x08, 0x05,  // 113:578
	0x02, 0x4A, 0x04, 0x03,  // 114:586
	0x02, 0x4E, 0x06, 0x04,  // 115:590
	0x02, 0x54, 0x06, 0x03,  // 116:596
	0x02, 0x5A, 0x08, 0x05,  // 117:602
	0x02, 0x62, 0x07, 0x04,  // 118:610
	0x02, 0x69, 0x0B, 0x06,  // 119:617
	0x02, 0x74, 0x08, 0x04,  // 120:628
	0x02, 0x7C, 0x07, 0x04,  // 121:636
	0x02, 0x83, 0x06, 0x04,  // 122:643
	0x02, 0x89, 0x05, 0x03,  // 123:649
	0x02, 0x8E, 0x06, 0x04,  // 124:654
	0x02, 0x94, 0x05, 0x03,  // 125:660
	0x02, 0x99, 0x07, 0x05,  // 126:665
	0x02, 0xA0, 0x08, 0x05,  // 127:672
	0x02, 0xA8, 0x08, 0x05,  // 128:680
	0x02, 0xB0, 0x08, 0x05,  // 129:688
	0x02, 0xB8, 0x08, 0x05,  // 130:696
	0x02, 0xC0, 0x08, 0x05,  // 131:704
	0x02, 0xC8, 0x08, 0x05,  // 132:712
	0x02, 0xD0, 0x08, 0x05,  // 133:720
	0x02, 0xD8, 0x08, 0x05,  // 134:728
	0x02, 0xE0, 0x08, 0x05,  // 135:736
	0x02, 0xE8, 0x08, 0x05,  // 136:744
	0x02, 0xF0, 0x08, 0x05,  // 137:752
	0x02, 0xF8, 0x08, 0x05,  // 138:760
	0x03, 0x00, 0x08, 0x05,  // 139:768
	0x03, 0x08, 0x08, 0x05,  // 140:776
	0x03, 0x10, 0x08, 0x05,  // 141:784
	0x03, 0x18, 0x08, 0x05,  // 142:792
	0x03, 0x20, 0x08, 0x05,  // 143:800
	0x03, 0x28, 0x08, 0x05,  // 144:808
	0x03, 0x30, 0x08, 0x05,  // 145:816
	0x03, 0x38, 0x08, 0x05,  // 146:824
	0x03, 0x40, 0x08, 0x05,  // 147:832
	0x03, 0x48, 0x08, 0x05,  // 148:840
	0x03, 0x50, 0x08, 0x05,  // 149:848
	0x03, 0x58, 0x08, 0x05,  // 150:856
	0x03, 0x60, 0x08, 0x05,  // 151:864
	0x03, 0x68, 0x08, 0x05,  // 152:872
	0x03, 0x70, 0x08, 0x05,  // 153:880
	0x03, 0x78, 0x08, 0x05,  // 154:888
	0x03, 0x80, 0x08, 0x05,  // 155:896
	0x03, 0x88, 0x08, 0x05,  // 156:904
	0x03, 0x90, 0x08, 0x05,  // 157:912
	0x03, 0x98, 0x08, 0x05,  // 158:920
	0x03, 0xA0, 0x08, 0x05,  // 159:928
	0xFF, 0xFF, 0x00, 0x02,  // 160:65535
	0x03, 0xA8, 0x04, 0x02,  // 161:936
	0x03, 0xAC, 0x07, 0x05,  // 162:940
	0x03, 0xB3, 0x08, 0x05,  // 163:947
	0x03, 0xBB, 0x07, 0x05,  // 164:955
	0x03, 0xC2, 0x07, 0x05,  // 165:962
	0x03, 0xC9, 0x06, 0x04,  // 166:969
	0x03, 0xCF, 0x07, 0x04,  // 167:975
	0x03, 0xD6, 0x03, 0x05,  // 168:982
	0x03, 0xD9, 0x0B, 0x07,  // 169:985
	0x03, 0xE4, 0x03, 0x03,  // 170:996
	0x03, 0xE7, 0x07, 0x04,  // 171:999
	0x03, 0xEE, 0x07, 0x05,  // 172:1006
	0x03, 0xF5, 0x03, 0x03,  // 173:1013
	0x03, 0xF8, 0x0B, 0x07,  // 174:1016
	0x04, 0x03, 0x07, 0x04,  // 175:1027
	0x04, 0x0A, 0x05, 0x03,  // 176:1034
	0x04, 0x0F, 0x08, 0x05,  // 177:1039
	0x04, 0x17, 0x05, 0x03,  // 178:1047
	0x04, 0x1C, 0x05, 0x03,  // 179:1052
	0x04, 0x21, 0x05, 0x05,  // 180:1057
	0x04, 0x26, 0x08, 0x05,  // 181:1062
	0x04, 0x2E, 0x08, 0x05,  // 182:1070
	0xFF, 0xFF, 0x00, 0x02,  // 183:65535
	0x04, 0x36, 0x04, 0x02,  // 184:1078
	0x04, 0x3A, 0x03, 0x03,  // 185:1082
	0x04, 0x3D, 0x05, 0x03,  // 186:1085
	0x04, 0x42, 0x07, 0x04,  // 187:1090
	0x04, 0x49, 0x0B, 0x06,  // 188:1097
	0x04, 0x54, 0x0C, 0x06,  // 189:1108
	0x04, 0x60, 0x0B, 0x06,  // 190:1120
	0x04, 0x6B, 0x06, 0x03,  // 191:1131
	0x04, 0x71, 0x0A, 0x05,  // 192:1137
	0x04, 0x7B, 0x0A, 0x05,  // 193:1147
	0x04, 0x85, 0x0A, 0x05,  // 194:1157
	0x04, 0x8F, 0x0A, 0x05,  // 195:1167
	0x04, 0x99, 0x0A, 0x05,  // 196:1177
	0x04, 0xA3, 0x0A, 0x05,  // 197:1187
	0x04, 0xAD, 0x0E, 0x07,  // 198:1197
	0x04, 0xBB, 0x0A, 0x05,  // 199:1211
	0x04, 0xC5, 0x08, 0x04,  // 200:1221
	0x04, 0xCD, 0x08, 0x04,  // 201:1229
	0x04, 0xD5, 0x08, 0x04,  // 202:1237
	0x04, 0xDD, 0x08, 0x04,  // 203:1245
	0x04, 0xE5, 0x02, 0x02,  // 204:1253
	0x04, 0xE7, 0x04, 0x02,  // 205:1255
	0x04, 0xEB, 0x04, 0x02,  // 206:1259
	0x04, 0xEF, 0x04, 0x02,  // 207:1263
	0x04, 0xF3, 0x09, 0x06,  // 208:1267
	0x04, 0xFC, 0x0A, 0x06,  // 209:1276
	0x05, 0x06, 0x0B, 0x06,  // 210:1286
	0x05, 0x11, 0x0B, 0x06,  // 211:1297
	0x05, 0x1C, 0x0B, 0x06,  // 212:1308
	0x05, 0x27, 0x0B, 0x06,  // 213:1319
	0x05, 0x32, 0x0B, 0x06,  // 214:1330
	0x05, 0x3D, 0x07, 0x05,  // 215:1341
	0x05, 0x44, 0x0B, 0x06,  // 216:1348
	0x05, 0x4F, 0x0A, 0x06,  // 217:1359
	0x05, 0x59, 0x0A, 0x06,  // 218:1369
	0x05, 0x63, 0x0A, 0x06,  // 219:1379
	0x05, 0x6D, 0x0A, 0x06,  // 220:1389
	0x05, 0x77, 0x07, 0x04,  // 221:1399
	0x05, 0x7E, 0x07, 0x05,  // 222:1406
	0x05, 0x85, 0x09, 0x05,  // 223:1413
	0x05, 0x8E, 0x08, 0x04,  // 224:1422
	0x05, 0x96, 0x08, 0x04,  // 225:1430
	0x05, 0x9E, 0x08, 0x04,  // 226:1438
	0x05, 0xA6, 0x08, 0x04,  // 227:1446
	0x05, 0xAE, 0x08, 0x04,  // 228:1454
	0x05, 0xB6, 0x08, 0x04,  // 229:1462
	0x05, 0xBE, 0x0C, 0x07,  // 230:1470
	0x05, 0xCA, 0x06, 0x04,  // 231:1482
	0x05, 0xD0, 0x08, 0x04,  // 232:1488
	0x05, 0xD8, 0x08, 0x04,  // 233:1496
	0x05, 0xE0, 0x08, 0x04,  // 234:1504
	0x05, 0xE8, 0x08, 0x04,  // 235:1512
	0x05, 0xF0, 0x02, 0x02,  // 236:1520
	0x05, 0xF2, 0x04, 0x02,  // 237:1522
	0x05, 0xF6, 0x04, 0x02,  // 238:1526
	0x05, 0xFA, 0x04, 0x02,  // 239:1530
	0x05, 0xFE, 0x08, 0x05,  // 240:1534
	0x06, 0x06, 0x08, 0x05,  // 241:1542
	0x06, 0x0E, 0x08, 0x05,  // 242:1550
	0x06, 0x16, 0x08, 0x05,  // 243:1558
	0x06, 0x1E, 0x08, 0x05,  // 244:1566
	0x06, 0x26, 0x08, 0x05,  // 245:1574
	0x06, 0x2E, 0x08, 0x05,  // 246:1582
	0x06, 0x36, 0x07, 0x05,  // 247:1590
	0x06, 0x3D, 0x08, 0x05,  // 248:1597
	0x06, 0x45, 0x08, 0x05,  // 249:1605
	0x06, 0x4D, 0x08, 0x05,  // 250:1613
	0x06, 0x55, 0x08, 0x05,  // 251:1621
	0x06, 0x5D, 0x08, 0x05,  // 252:1629
	0x06, 0x65, 0x07, 0x04,  // 253:1637
	0x06, 0x6C, 0x08, 0x05,  // 254:1644
	0x06, 0x74, 0x07, 0x04,  // 255:1652

	// Font Data:
	0x00,0x00,0x70,0x01,	// 33
	0x00,0x00,0x10,0x00,0x18,	// 34
	0x00,0x00,0xE0,0x01,0x90,0x01,0xF0,	// 35
	0x00,0x00,0x30,0x01,0xF8,0x01,0xC0,	// 36
	0x30,0x00,0x48,0x01,0xB0,0x00,0x60,0x00,0xB8,0x01,0xC0,0x01,	// 37
	0x80,0x00,0x78,0x01,0x68,0x01,0x90,0x01,0x80,0x01,	// 38
	0x10,	// 39
	0xE0,0x01,0x18,0x02,	// 40
	0x08,0x00,0xF0,0x03,	// 41
	0x10,0x00,0x30,0x00,0x38,0x00,0x10,	// 42
	0x00,0x00,0x40,0x00,0xF0,0x00,0x40,	// 43
	0x00,0x02,	// 44
	0x00,0x00,0x40,	// 45
	0x00,0x00,0x00,0x01,	// 46
	0x80,0x01,0x60,0x00,0x18,	// 47
	0xF0,0x00,0x08,0x01,0x08,0x01,0xF0,0x01,	// 48
	0x00,0x00,0x10,0x00,0xF8,0x01,	// 49
	0x00,0x01,0x88,0x01,0x48,0x01,0x30,0x01,	// 50
	0x00,0x01,0x08,0x01,0x48,0x01,0xF0,0x01,	// 51
	0xC0,0x00,0xA0,0x00,0x90,0x00,0xF8,0x01,	// 52
	0x00,0x00,0x38,0x01,0x28,0x01,0xC8,0x01,	// 53
	0xE0,0x00,0x50,0x01,0x28,0x01,0xC8,0x01,	// 54
	0x08,0x00,0x08,0x01,0xC8,0x00,0x38,	// 55
	0x90,0x00,0x68,0x01,0x48,0x01,0xF0,0x01,	// 56
	0x30,0x00,0x48,0x01,0x48,0x01,0xF0,	// 57
	0x00,0x00,0x00,0x01,	// 58
	0x00,0x02,	// 59
	0x00,0x00,0x60,0x00,0xA0,0x00,0x90,	// 60
	0x20,0x00,0x60,0x00,0x60,0x00,0x60,	// 61
	0x90,0x00,0x90,0x00,0x60,0x00,0x40,	// 62
	0x08,0x00,0x48,0x01,0x38,	// 63
	0xE0,0x00,0x10,0x01,0xE8,0x02,0xA8,0x02,0xE8,0x02,0x90,0x00,0xE0,	// 64
	0x80,0x01,0x60,0x00,0x58,0x00,0x60,0x00,0x80,0x01,	// 65
	0x00,0x00,0xF8,0x01,0x48,0x01,0x28,0x01,0xD0,	// 66
	0x60,0x00,0x90,0x01,0x08,0x01,0x08,0x01,0x08,0x01,	// 67
	0x00,0x00,0xF8,0x01,0x08,0x01,0x08,0x01,0xF0,	// 68
	0x00,0x00,0xF8,0x01,0x48,0x01,0x08,0x01,	// 69
	0x00,0x00,0xF8,0x01,0x48,0x00,0x48,	// 70
	0x60,0x00,0x90,0x01,0x08,0x01,0x48,0x01,0xC8,0x01,	// 71
	0x00,0x00,0xF0,0x01,0x40,0x00,0x40,0x00,0xF8,0x01,	// 72
	0x00,0x00,0xF0,0x01,	// 73
	0xF0,0x03,	// 74
	0x00,0x00,0xF0,0x01,0x60,0x00,0x90,0x00,0x08,0x01,	// 75
	0x00,0x00,0xF0,0x01,0x00,0x01,0x00,0x01,	// 76
	0x00,0x00,0xF8,0x01,0x60,0x00,0x80,0x01,0x60,0x00,0xF8,0x01,	// 77
	0x00,0x00,0xF8,0x01,0x20,0x00,0xC0,0x00,0xF0,0x01,	// 78
	0x60,0x00,0x90,0x01,0x08,0x01,0x08,0x01,0x08,0x01,0xF0,	// 79
	0x00,0x00,0xF8,0x01,0x48,0x00,0x38,	// 80
	0x60,0x00,0x90,0x01,0x08,0x01,0x08,0x01,0x08,0x03,0xF0,	// 81
	0x00,0x00,0xF8,0x01,0x48,0x00,0xA8,0x00,0x10,0x01,	// 82
	0x10,0x01,0x28,0x01,0x48,0x01,0xC8,0x01,	// 83
	0x08,0x00,0x08,0x00,0xF8,0x01,0x08,	// 84
	0x00,0x00,0xF0,0x01,0x00,0x01,0x00,0x01,0xF8,0x01,	// 85
	0x18,0x00,0xE0,0x00,0x80,0x01,0x70,0x00,0x08,	// 86
	0x18,0x00,0xE0,0x01,0xE0,0x00,0x18,0x00,0xE0,0x00,0x80,0x01,0x70,	// 87
	0x08,0x01,0x90,0x00,0x60,0x00,0x90,0x01,	// 88
	0x08,0x00,0x30,0x00,0xE0,0x01,0x10,	// 89
	0x08,0x01,0x88,0x01,0x68,0x01,0x18,0x01,	// 90
	0x00,0x00,0xF8,0x03,	// 91
	0x18,0x00,0xE0,0x00,0x00,0x01,	// 92
	0x08,0x00,0xF8,0x03,	// 93
	0x40,0x00,0x30,0x00,0x10,0x00,0x60,	// 94
	0x00,0x02,0x00,0x02,0x00,0x02,	// 95
	0x00,0x00,0x00,0x00,0x08,	// 96
	0x80,0x00,0x60,0x01,0x60,0x01,0xE0,0x01,	// 97
	0x00,0x00,0xF8,0x01,0x10,0x01,0xE0,0x01,	// 98
	0xC0,0x00,0x20,0x01,0x20,0x01,	// 99
	0xC0,0x00,0x20,0x01,0x10,0x01,0xF8,0x01,	// 100
	0xC0,0x00,0x60,0x01,0x60,0x01,0x60,0x01,	// 101
	0x00,0x00,0xF8,0x01,0x08,	// 102
	0x60,0x06,0xA0,0x05,0xA0,0x05,0x60,0x07,	// 103
	0x00,0x00,0xF8,0x01,0x10,0x00,0xE0,0x01,	// 104
	0x00,0x00,0xE0,0x01,	// 105
	0xE0,0x07,	// 106
	0x00,0x00,0xF8,0x01,0xA0,0x00,0x10,0x01,	// 107
	0x00,0x00,0xF8,0x01,	// 108
	0x00,0x00,0xE0,0x01,0x20,0x00,0xE0,0x01,0x20,0x00,0x20,0x00,0xE0,0x01,	// 109
	0x00,0x00,0xE0,0x01,0x20,0x00,0xE0,0x01,	// 110
	0xC0,0x00,0x20,0x01,0x20,0x01,0xE0,0x01,	// 111
	0x00,0x00,0xE0,0x03,0x20,0x01,0xE0,0x01,	// 112
	0xC0,0x00,0x20,0x01,0x20,0x01,0xE0,0x03,	// 113
	0x00,0x00,0xE0,0x01,	// 114
	0x20,0x01,0x60,0x01,0xA0,0x01,	// 115
	0x00,0x00,0xF0,0x01,0x00,0x01,	// 116
	0x00,0x00,0xE0,0x01,0x00,0x01,0xE0,0x01,	// 117
	0x20,0x00,0xC0,0x01,0x80,0x01,0x60,	// 118
	0x60,0x00,0x80,0x01,0x40,0x00,0x60,0x00,0x80,0x01,0x60,	// 119
	0x00,0x01,0xE0,0x00,0xC0,0x00,0x20,0x01,	// 120
	0x20,0x04,0xC0,0x06,0x80,0x01,0x60,	// 121
	0x00,0x01,0xA0,0x01,0x60,0x01,	// 122
	0x40,0x00,0xF0,0x03,0x08,	// 123
	0x00,0x00,0x00,0x00,0xF8,0x03,	// 124
	0x08,0x00,0xF0,0x03,0x40,	// 125
	0x40,0x00,0x40,0x00,0x40,0x00,0x40,	// 126
	0x00,0x00,0xF8,0x01,0x08,0x01,0xF8,0x01,	// 127
	0x00,0x00,0xF8,0x01,0x08,0x01,0xF8,0x01,	// 128
	0x00,0x00,0xF8,0x01,0x08,0x01,0xF8,0x01,	// 129
	0x00,0x00,0xF8,0x01,0x08,0x01,0xF8,0x01,	// 130
	0x00,0x00,0xF8,0x01,0x08,0x01,0xF8,0x01,	// 131
	0x00,0x00,0xF8,0x01,0x08,0x01,0xF8,0x01,	// 132
	0x00,0x00,0xF8,0x01,0x08,0x01,0xF8,0x01,	// 133
	0x00,0x00,0xF8,0x01,0x08,0x01,0xF8,0x01,	// 134
	0x00,0x00,0xF8,0x01,0x08,0x01,0xF8,0x01,	// 135
	0x00,0x00,0xF8,0x01,0x08,0x01,0xF8,0x01,	// 136
	0x00,0x00,0xF8,0x01,0x08,0x01,0xF8,0x01,	// 137
	0x00,0x00,0xF8,0x01,0x08,0x01,0xF8,0x01,	// 138
	0x00,0x00,0xF8,0x01,0x08,0x01,0xF8,0x01,	// 139
	0x00,0x00,0xF8,0x01,0x08,0x01,0xF8,0x01,	// 140
	0x00,0x00,0xF8,0x01,0x08,0x01,0xF8,0x01,	// 141
	0x00,0x00,0xF8,0x01,0x08,0x01,0xF8,0x01,	// 142
	0x00,0x00,0xF8,0x01,0x08,0x01,0xF8,0x01,	// 143
	0x00,0x00,0xF8,0x01,0x08,0x01,0xF8,0x01,	// 144
	0x00,0x00,0xF8,0x01,0x08,0x01,0xF8,0x01,	// 145
	0x00,0x00,0xF8,0x01,0x08,0x01,0xF8,0x01,	// 146
	0x00,0x00,0xF8,0x01,0x08,0x01,0xF8,0x01,	// 147
	0x00,0x00,0xF8,0x01,0x08,0x01,0xF8,0x01,	// 148
	0x00,0x00,0xF8,0x01,0x08,0x01,0xF8,0x01,	// 149
	0x00,0x00,0xF8,0x01,0x08,0x01,0xF8,0x01,	// 150
	0x00,0x00,0xF8,0x01,0x08,0x01,0xF8,0x01,	// 151
	0x00,0x00,0xF8,0x01,0x08,0x01,0xF8,0x01,	// 152
	0x00,0x00,0xF8,0x01,0x08,0x01,0xF8,0x01,	// 153
	0x00,0x00,0xF8,0x01,0x08,0x01,0xF8,0x01,	// 154
	0x00,0x00,0xF8,0x01,0x08,0x01,0xF8,0x01,	// 155
	0x00,0x00,0xF8,0x01,0x08,0x01,0xF8,0x01,	// 156
	0x00,0x00,0xF8,0x01,0x08,0x01,0xF8,0x01,	// 157
	0x00,0x00,0xF8,0x01,0x08,0x01,0xF8,0x01,	// 158
	0x00,0x00,0xF8,0x01,0x08,0x01,0xF8,0x01,	// 159
	0x00,0x00,0x80,0x03,	// 161
	0x00,0x00,0xF0,0x00,0x08,0x01,0x10,	// 162
	0x00,0x01,0xF0,0x01,0x48,0x01,0x08,0x01,	// 163
	0x00,0x00,0xE0,0x00,0x90,0x00,0xE0,	// 164
	0x08,0x00,0xF0,0x00,0xE0,0x01,0xD0,	// 165
	0x00,0x00,0x00,0x00,0x18,0x03,	// 166
	0x20,0x01,0x58,0x01,0xA8,0x01,0xE0,	// 167
	0x00,0x00,0x08,	// 168
	0xE0,0x00,0x10,0x01,0xE8,0x01,0x98,0x01,0x08,0x01,0xF0,	// 169
	0x28,0x00,0x38,	// 170
	0x40,0x00,0xA0,0x00,0xC0,0x00,0x20,	// 171
	0x00,0x00,0x40,0x00,0x40,0x00,0x40,	// 172
	0x00,0x00,0x40,	// 173
	0xE0,0x00,0x10,0x01,0xF8,0x01,0x58,0x01,0xA8,0x01,0xF0,	// 174
	0x04,0x00,0x04,0x00,0x04,0x00,0x04,	// 175
	0x00,0x00,0x38,0x00,0x18,	// 176
	0x00,0x00,0x40,0x01,0xF0,0x01,0x40,0x01,	// 177
	0x48,0x00,0x68,0x00,0x50,	// 178
	0x48,0x00,0x58,0x00,0x30,	// 179
	0x00,0x00,0x00,0x00,0x08,	// 180
	0x00,0x00,0xE0,0x03,0x00,0x01,0xE0,0x01,	// 181
	0x30,0x00,0x78,0x00,0xF8,0x01,0xF8,0x01,	// 182
	0x00,0x06,0x00,0x04,	// 184
	0x00,0x00,0x78,	// 185
	0x30,0x00,0x28,0x00,0x30,	// 186
	0x20,0x00,0xC0,0x00,0xA0,0x00,0x40,	// 187
	0x00,0x00,0x78,0x00,0x80,0x01,0xE0,0x00,0xD0,0x00,0x80,	// 188
	0x00,0x00,0xF8,0x01,0x40,0x00,0x30,0x01,0xA0,0x01,0x40,0x01,	// 189
	0x48,0x00,0x58,0x00,0xB0,0x01,0xE0,0x00,0xD0,0x00,0x80,	// 190
	0x00,0x03,0x80,0x04,0x00,0x04,	// 191
	0x80,0x01,0x60,0x00,0x5C,0x00,0x60,0x00,0x80,0x01,	// 192
	0x80,0x01,0x60,0x00,0x58,0x00,0x64,0x00,0x80,0x01,	// 193
	0x80,0x01,0x60,0x00,0x5C,0x00,0x60,0x00,0x80,0x01,	// 194
	0x80,0x01,0x64,0x00,0x5C,0x00,0x64,0x00,0x80,0x01,	// 195
	0x80,0x01,0x64,0x00,0x58,0x00,0x60,0x00,0x80,0x01,	// 196
	0x80,0x01,0x64,0x00,0x5C,0x00,0x60,0x00,0x80,0x01,	// 197
	0x00,0x01,0xE0,0x00,0x50,0x00,0xF8,0x00,0x48,0x01,0x48,0x01,0x08,0x01,	// 198
	0x60,0x00,0x90,0x01,0x08,0x07,0x08,0x05,0x08,0x01,	// 199
	0x00,0x00,0xF8,0x01,0x4C,0x01,0x08,0x01,	// 200
	0x00,0x00,0xF8,0x01,0x4C,0x01,0x08,0x01,	// 201
	0x00,0x00,0xF8,0x01,0x4C,0x01,0x08,0x01,	// 202
	0x00,0x00,0xFC,0x01,0x48,0x01,0x08,0x01,	// 203
	0xF4,0x01,	// 204
	0x00,0x00,0xF4,0x01,	// 205
	0x00,0x00,0xF4,0x01,	// 206
	0x04,0x00,0xF0,0x01,	// 207
	0x00,0x00,0xF8,0x01,0x08,0x01,0x08,0x01,0xF0,	// 208
	0x00,0x00,0xF8,0x01,0x24,0x00,0xC4,0x00,0xF4,0x01,	// 209
	0x60,0x00,0x90,0x01,0x0C,0x01,0x08,0x01,0x08,0x01,0xF0,	// 210
	0x60,0x00,0x90,0x01,0x08,0x01,0x0C,0x01,0x08,0x01,0xF0,	// 211
	0x60,0x00,0x90,0x01,0x08,0x01,0x0C,0x01,0x08,0x01,0xF0,	// 212
	0x60,0x00,0x90,0x01,0x0C,0x01,0x0C,0x01,0x0C,0x01,0xF0,	// 213
	0x60,0x00,0x90,0x01,0x0C,0x01,0x08,0x01,0x08,0x01,0xF0,	// 214
	0x00,0x00,0x60,0x00,0x60,0x00,0x80,	// 215
	0x60,0x00,0x90,0x01,0x48,0x01,0x28,0x01,0x10,0x01,0xE0,	// 216
	0x00,0x00,0xF0,0x01,0x04,0x01,0x00,0x01,0xF8,0x01,	// 217
	0x00,0x00,0xF0,0x01,0x00,0x01,0x04,0x01,0xF8,0x01,	// 218
	0x00,0x00,0xF0,0x01,0x04,0x01,0x00,0x01,0xF8,0x01,	// 219
	0x00,0x00,0xF0,0x01,0x04,0x01,0x00,0x01,0xF8,0x01,	// 220
	0x08,0x00,0x30,0x00,0xE4,0x01,0x10,	// 221
	0x00,0x00,0xF0,0x01,0x90,0x00,0xF0,	// 222
	0x00,0x00,0xF8,0x01,0x28,0x01,0x58,0x01,0x80,	// 223
	0x80,0x00,0x60,0x01,0x58,0x01,0xE0,0x01,	// 224
	0x80,0x00,0x60,0x01,0x58,0x01,0xE0,0x01,	// 225
	0x80,0x00,0x60,0x01,0x58,0x01,0xE0,0x01,	// 226
	0x80,0x00,0x68,0x01,0x58,0x01,0xE8,0x01,	// 227
	0x80,0x00,0x68,0x01,0x50,0x01,0xE0,0x01,	// 228
	0x80,0x00,0x68,0x01,0x58,0x01,0xE0,0x01,	// 229
	0x80,0x00,0x60,0x01,0x60,0x01,0xE0,0x00,0x60,0x01,0x60,0x01,	// 230
	0xC0,0x00,0x20,0x07,0x20,0x05,	// 231
	0xC0,0x00,0x60,0x01,0x58,0x01,0x60,0x01,	// 232
	0xC0,0x00,0x60,0x01,0x58,0x01,0x60,0x01,	// 233
	0xC0,0x00,0x60,0x01,0x58,0x01,0x60,0x01,	// 234
	0xC0,0x00,0x68,0x01,0x50,0x01,0x60,0x01,	// 235
	0xE8,0x01,	// 236
	0x00,0x00,0xE8,0x01,	// 237
	0x00,0x00,0xE8,0x01,	// 238
	0x08,0x00,0xE0,0x01,	// 239
	0xC0,0x00,0x30,0x01,0x28,0x01,0xF8,0x01,	// 240
	0x00,0x00,0xE8,0x01,0x18,0x00,0xE8,0x01,	// 241
	0xC0,0x00,0x20,0x01,0x18,0x01,0xE0,0x01,	// 242
	0xC0,0x00,0x20,0x01,0x18,0x01,0xE0,0x01,	// 243
	0xC0,0x00,0x20,0x01,0x18,0x01,0xE0,0x01,	// 244
	0xC0,0x00,0x28,0x01,0x18,0x01,0xE8,0x01,	// 245
	0xC0,0x00,0x28,0x01,0x10,0x01,0xE0,0x01,	// 246
	0x00,0x00,0x40,0x00,0xD0,0x00,0x40,	// 247
	0xC0,0x00,0xA0,0x01,0x50,0x01,0xE0,0x01,	// 248
	0x00,0x00,0xE0,0x01,0x08,0x01,0xE0,0x01,	// 249
	0x00,0x00,0xE0,0x01,0x08,0x01,0xE0,0x01,	// 250
	0x00,0x00,0xE0,0x01,0x08,0x01,0xE0,0x01,	// 251
	0x00,0x00,0xE8,0x01,0x00,0x01,0xE0,0x01,	// 252
	0x20,0x04,0xC0,0x06,0x88,0x01,0x60,	// 253
	0x00,0x00,0xF8,0x03,0x10,0x01,0xE0,0x01,	// 254
	0x20,0x04,0xC8,0x06,0x80,0x01,0x60	// 255
};
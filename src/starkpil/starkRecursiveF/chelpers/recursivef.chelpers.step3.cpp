#include "goldilocks_cubic_extension.hpp"
#include "zhInv.hpp"
#include "starks.hpp"
#include "constant_pols_starks.hpp"
#include "starkRecursiveFSteps.hpp"


void StarkRecursiveFSteps::step3_first(StepsParams &params, uint64_t i) {
     
     Goldilocks::Element tmp_141;
     Goldilocks::copy(tmp_141, params.pols[0 + i*12]);
     Goldilocks3::Element tmp_81;
     Goldilocks3::mul(tmp_81, (Goldilocks::Element &)*params.x_n[i], (Goldilocks3::Element &)*params.challenges[3]);
     Goldilocks3::Element tmp_82;
     Goldilocks3::add(tmp_82, tmp_141, tmp_81);
     Goldilocks3::Element tmp_142;
     Goldilocks3::add(tmp_142, tmp_82, (Goldilocks3::Element &)*params.challenges[2]);
     Goldilocks::Element tmp_143;
     Goldilocks::copy(tmp_143, params.pols[1 + i*12]);
     Goldilocks3::Element tmp_83;
     Goldilocks3::mul(tmp_83, Goldilocks::fromU64(12275445934081160404ULL), (Goldilocks3::Element &)*params.challenges[3]);
     Goldilocks3::Element tmp_84;
     Goldilocks3::mul(tmp_84, (Goldilocks::Element &)*params.x_n[i], tmp_83);
     Goldilocks3::Element tmp_85;
     Goldilocks3::add(tmp_85, tmp_143, tmp_84);
     Goldilocks3::Element tmp_86;
     Goldilocks3::add(tmp_86, tmp_85, (Goldilocks3::Element &)*params.challenges[2]);
     Goldilocks3::Element tmp_144;
     Goldilocks3::mul(tmp_144, tmp_142, tmp_86);
     Goldilocks::Element tmp_145;
     Goldilocks::copy(tmp_145, params.pols[2 + i*12]);
     Goldilocks3::Element tmp_87;
     Goldilocks3::mul(tmp_87, Goldilocks::fromU64(4756475762779100925ULL), (Goldilocks3::Element &)*params.challenges[3]);
     Goldilocks3::Element tmp_88;
     Goldilocks3::mul(tmp_88, (Goldilocks::Element &)*params.x_n[i], tmp_87);
     Goldilocks3::Element tmp_89;
     Goldilocks3::add(tmp_89, tmp_145, tmp_88);
     Goldilocks3::Element tmp_90;
     Goldilocks3::add(tmp_90, tmp_89, (Goldilocks3::Element &)*params.challenges[2]);
     Goldilocks3::Element tmp_146;
     Goldilocks3::mul(tmp_146, tmp_144, tmp_90);
     Goldilocks::Element tmp_147;
     Goldilocks::copy(tmp_147, params.pols[3 + i*12]);
     Goldilocks3::Element tmp_91;
     Goldilocks3::mul(tmp_91, Goldilocks::fromU64(1279992132519201448ULL), (Goldilocks3::Element &)*params.challenges[3]);
     Goldilocks3::Element tmp_92;
     Goldilocks3::mul(tmp_92, (Goldilocks::Element &)*params.x_n[i], tmp_91);
     Goldilocks3::Element tmp_93;
     Goldilocks3::add(tmp_93, tmp_147, tmp_92);
     Goldilocks3::Element tmp_94;
     Goldilocks3::add(tmp_94, tmp_93, (Goldilocks3::Element &)*params.challenges[2]);
     Goldilocks3::Element tmp_148;
     Goldilocks3::mul(tmp_148, tmp_146, tmp_94);
     Goldilocks::Element tmp_149;
     Goldilocks::copy(tmp_149, params.pols[4 + i*12]);
     Goldilocks3::Element tmp_95;
     Goldilocks3::mul(tmp_95, Goldilocks::fromU64(8312008622371998338ULL), (Goldilocks3::Element &)*params.challenges[3]);
     Goldilocks3::Element tmp_96;
     Goldilocks3::mul(tmp_96, (Goldilocks::Element &)*params.x_n[i], tmp_95);
     Goldilocks3::Element tmp_97;
     Goldilocks3::add(tmp_97, tmp_149, tmp_96);
     Goldilocks3::Element tmp_98;
     Goldilocks3::add(tmp_98, tmp_97, (Goldilocks3::Element &)*params.challenges[2]);
     Goldilocks3::mul((Goldilocks3::Element &)(params.pols[50331651 + i*15]), tmp_148, tmp_98);
     Goldilocks::Element tmp_150;
     Goldilocks::copy(tmp_150,  params.pConstPols->getElement(4,i));
     Goldilocks3::Element tmp_99;
     Goldilocks3::mul(tmp_99, tmp_150, (Goldilocks3::Element &)*params.challenges[3]);
     Goldilocks3::Element tmp_100;
     Goldilocks3::add(tmp_100, tmp_141, tmp_99);
     Goldilocks3::Element tmp_151;
     Goldilocks3::add(tmp_151, tmp_100, (Goldilocks3::Element &)*params.challenges[2]);
     Goldilocks::Element tmp_152;
     Goldilocks::copy(tmp_152,  params.pConstPols->getElement(5,i));
     Goldilocks3::Element tmp_101;
     Goldilocks3::mul(tmp_101, tmp_152, (Goldilocks3::Element &)*params.challenges[3]);
     Goldilocks3::Element tmp_102;
     Goldilocks3::add(tmp_102, tmp_143, tmp_101);
     Goldilocks3::Element tmp_103;
     Goldilocks3::add(tmp_103, tmp_102, (Goldilocks3::Element &)*params.challenges[2]);
     Goldilocks3::Element tmp_153;
     Goldilocks3::mul(tmp_153, tmp_151, tmp_103);
     Goldilocks::Element tmp_154;
     Goldilocks::copy(tmp_154,  params.pConstPols->getElement(6,i));
     Goldilocks3::Element tmp_104;
     Goldilocks3::mul(tmp_104, tmp_154, (Goldilocks3::Element &)*params.challenges[3]);
     Goldilocks3::Element tmp_105;
     Goldilocks3::add(tmp_105, tmp_145, tmp_104);
     Goldilocks3::Element tmp_106;
     Goldilocks3::add(tmp_106, tmp_105, (Goldilocks3::Element &)*params.challenges[2]);
     Goldilocks3::Element tmp_155;
     Goldilocks3::mul(tmp_155, tmp_153, tmp_106);
     Goldilocks::Element tmp_156;
     Goldilocks::copy(tmp_156,  params.pConstPols->getElement(7,i));
     Goldilocks3::Element tmp_107;
     Goldilocks3::mul(tmp_107, tmp_156, (Goldilocks3::Element &)*params.challenges[3]);
     Goldilocks3::Element tmp_108;
     Goldilocks3::add(tmp_108, tmp_147, tmp_107);
     Goldilocks3::Element tmp_109;
     Goldilocks3::add(tmp_109, tmp_108, (Goldilocks3::Element &)*params.challenges[2]);
     Goldilocks3::Element tmp_157;
     Goldilocks3::mul(tmp_157, tmp_155, tmp_109);
     Goldilocks::Element tmp_158;
     Goldilocks::copy(tmp_158,  params.pConstPols->getElement(8,i));
     Goldilocks3::Element tmp_110;
     Goldilocks3::mul(tmp_110, tmp_158, (Goldilocks3::Element &)*params.challenges[3]);
     Goldilocks3::Element tmp_111;
     Goldilocks3::add(tmp_111, tmp_149, tmp_110);
     Goldilocks3::Element tmp_112;
     Goldilocks3::add(tmp_112, tmp_111, (Goldilocks3::Element &)*params.challenges[2]);
     Goldilocks3::mul((Goldilocks3::Element &)(params.pols[50331654 + i*15]), tmp_157, tmp_112);
     Goldilocks::Element tmp_159;
     Goldilocks::copy(tmp_159, params.pols[5 + i*12]);
     Goldilocks3::Element tmp_113;
     Goldilocks3::mul(tmp_113, Goldilocks::fromU64(7781028390488215464ULL), (Goldilocks3::Element &)*params.challenges[3]);
     Goldilocks3::Element tmp_114;
     Goldilocks3::mul(tmp_114, (Goldilocks::Element &)*params.x_n[i], tmp_113);
     Goldilocks3::Element tmp_115;
     Goldilocks3::add(tmp_115, tmp_159, tmp_114);
     Goldilocks3::Element tmp_116;
     Goldilocks3::add(tmp_116, tmp_115, (Goldilocks3::Element &)*params.challenges[2]);
     Goldilocks3::Element tmp_160;
     Goldilocks3::mul(tmp_160, (Goldilocks3::Element &)(params.pols[50331651 + i*15]), tmp_116);
     Goldilocks::Element tmp_161;
     Goldilocks::copy(tmp_161, params.pols[6 + i*12]);
     Goldilocks3::Element tmp_117;
     Goldilocks3::mul(tmp_117, Goldilocks::fromU64(11302600489504509467ULL), (Goldilocks3::Element &)*params.challenges[3]);
     Goldilocks3::Element tmp_118;
     Goldilocks3::mul(tmp_118, (Goldilocks::Element &)*params.x_n[i], tmp_117);
     Goldilocks3::Element tmp_119;
     Goldilocks3::add(tmp_119, tmp_161, tmp_118);
     Goldilocks3::Element tmp_120;
     Goldilocks3::add(tmp_120, tmp_119, (Goldilocks3::Element &)*params.challenges[2]);
     Goldilocks3::Element tmp_162;
     Goldilocks3::mul(tmp_162, tmp_160, tmp_120);
     Goldilocks::Element tmp_163;
     Goldilocks::copy(tmp_163, params.pols[7 + i*12]);
     Goldilocks3::Element tmp_121;
     Goldilocks3::mul(tmp_121, Goldilocks::fromU64(4549350404001778198ULL), (Goldilocks3::Element &)*params.challenges[3]);
     Goldilocks3::Element tmp_122;
     Goldilocks3::mul(tmp_122, (Goldilocks::Element &)*params.x_n[i], tmp_121);
     Goldilocks3::Element tmp_123;
     Goldilocks3::add(tmp_123, tmp_163, tmp_122);
     Goldilocks3::Element tmp_124;
     Goldilocks3::add(tmp_124, tmp_123, (Goldilocks3::Element &)*params.challenges[2]);
     Goldilocks3::Element tmp_164;
     Goldilocks3::mul(tmp_164, tmp_162, tmp_124);
     Goldilocks::Element tmp_165;
     Goldilocks::copy(tmp_165, params.pols[8 + i*12]);
     Goldilocks3::Element tmp_125;
     Goldilocks3::mul(tmp_125, Goldilocks::fromU64(3688660304411827445ULL), (Goldilocks3::Element &)*params.challenges[3]);
     Goldilocks3::Element tmp_126;
     Goldilocks3::mul(tmp_126, (Goldilocks::Element &)*params.x_n[i], tmp_125);
     Goldilocks3::Element tmp_127;
     Goldilocks3::add(tmp_127, tmp_165, tmp_126);
     Goldilocks3::Element tmp_128;
     Goldilocks3::add(tmp_128, tmp_127, (Goldilocks3::Element &)*params.challenges[2]);
     Goldilocks3::mul((Goldilocks3::Element &)(params.pols[50331657 + i*15]), tmp_164, tmp_128);
     Goldilocks::Element tmp_166;
     Goldilocks::copy(tmp_166,  params.pConstPols->getElement(9,i));
     Goldilocks3::Element tmp_129;
     Goldilocks3::mul(tmp_129, tmp_166, (Goldilocks3::Element &)*params.challenges[3]);
     Goldilocks3::Element tmp_130;
     Goldilocks3::add(tmp_130, tmp_159, tmp_129);
     Goldilocks3::Element tmp_131;
     Goldilocks3::add(tmp_131, tmp_130, (Goldilocks3::Element &)*params.challenges[2]);
     Goldilocks3::Element tmp_167;
     Goldilocks3::mul(tmp_167, (Goldilocks3::Element &)(params.pols[50331654 + i*15]), tmp_131);
     Goldilocks::Element tmp_168;
     Goldilocks::copy(tmp_168,  params.pConstPols->getElement(10,i));
     Goldilocks3::Element tmp_132;
     Goldilocks3::mul(tmp_132, tmp_168, (Goldilocks3::Element &)*params.challenges[3]);
     Goldilocks3::Element tmp_133;
     Goldilocks3::add(tmp_133, tmp_161, tmp_132);
     Goldilocks3::Element tmp_134;
     Goldilocks3::add(tmp_134, tmp_133, (Goldilocks3::Element &)*params.challenges[2]);
     Goldilocks3::Element tmp_169;
     Goldilocks3::mul(tmp_169, tmp_167, tmp_134);
     Goldilocks::Element tmp_170;
     Goldilocks::copy(tmp_170,  params.pConstPols->getElement(11,i));
     Goldilocks3::Element tmp_135;
     Goldilocks3::mul(tmp_135, tmp_170, (Goldilocks3::Element &)*params.challenges[3]);
     Goldilocks3::Element tmp_136;
     Goldilocks3::add(tmp_136, tmp_163, tmp_135);
     Goldilocks3::Element tmp_137;
     Goldilocks3::add(tmp_137, tmp_136, (Goldilocks3::Element &)*params.challenges[2]);
     Goldilocks3::Element tmp_171;
     Goldilocks3::mul(tmp_171, tmp_169, tmp_137);
     Goldilocks::Element tmp_172;
     Goldilocks::copy(tmp_172,  params.pConstPols->getElement(12,i));
     Goldilocks3::Element tmp_138;
     Goldilocks3::mul(tmp_138, tmp_172, (Goldilocks3::Element &)*params.challenges[3]);
     Goldilocks3::Element tmp_139;
     Goldilocks3::add(tmp_139, tmp_165, tmp_138);
     Goldilocks3::Element tmp_140;
     Goldilocks3::add(tmp_140, tmp_139, (Goldilocks3::Element &)*params.challenges[2]);
     Goldilocks3::mul((Goldilocks3::Element &)(params.pols[50331660 + i*15]), tmp_171, tmp_140);
}

void StarkRecursiveFSteps::step3_i(StepsParams &params, uint64_t i) {
     Goldilocks::Element tmp_141;
     Goldilocks::copy(tmp_141, params.pols[0 + i*12]);
     Goldilocks3::Element tmp_81;
     Goldilocks3::mul(tmp_81, (Goldilocks::Element &)*params.x_n[i], (Goldilocks3::Element &)*params.challenges[3]);
     Goldilocks3::Element tmp_82;
     Goldilocks3::add(tmp_82, tmp_141, tmp_81);
     Goldilocks3::Element tmp_142;
     Goldilocks3::add(tmp_142, tmp_82, (Goldilocks3::Element &)*params.challenges[2]);
     Goldilocks::Element tmp_143;
     Goldilocks::copy(tmp_143, params.pols[1 + i*12]);
     Goldilocks3::Element tmp_83;
     Goldilocks3::mul(tmp_83, Goldilocks::fromU64(12275445934081160404ULL), (Goldilocks3::Element &)*params.challenges[3]);
     Goldilocks3::Element tmp_84;
     Goldilocks3::mul(tmp_84, (Goldilocks::Element &)*params.x_n[i], tmp_83);
     Goldilocks3::Element tmp_85;
     Goldilocks3::add(tmp_85, tmp_143, tmp_84);
     Goldilocks3::Element tmp_86;
     Goldilocks3::add(tmp_86, tmp_85, (Goldilocks3::Element &)*params.challenges[2]);
     Goldilocks3::Element tmp_144;
     Goldilocks3::mul(tmp_144, tmp_142, tmp_86);
     Goldilocks::Element tmp_145;
     Goldilocks::copy(tmp_145, params.pols[2 + i*12]);
     Goldilocks3::Element tmp_87;
     Goldilocks3::mul(tmp_87, Goldilocks::fromU64(4756475762779100925ULL), (Goldilocks3::Element &)*params.challenges[3]);
     Goldilocks3::Element tmp_88;
     Goldilocks3::mul(tmp_88, (Goldilocks::Element &)*params.x_n[i], tmp_87);
     Goldilocks3::Element tmp_89;
     Goldilocks3::add(tmp_89, tmp_145, tmp_88);
     Goldilocks3::Element tmp_90;
     Goldilocks3::add(tmp_90, tmp_89, (Goldilocks3::Element &)*params.challenges[2]);
     Goldilocks3::Element tmp_146;
     Goldilocks3::mul(tmp_146, tmp_144, tmp_90);
     Goldilocks::Element tmp_147;
     Goldilocks::copy(tmp_147, params.pols[3 + i*12]);
     Goldilocks3::Element tmp_91;
     Goldilocks3::mul(tmp_91, Goldilocks::fromU64(1279992132519201448ULL), (Goldilocks3::Element &)*params.challenges[3]);
     Goldilocks3::Element tmp_92;
     Goldilocks3::mul(tmp_92, (Goldilocks::Element &)*params.x_n[i], tmp_91);
     Goldilocks3::Element tmp_93;
     Goldilocks3::add(tmp_93, tmp_147, tmp_92);
     Goldilocks3::Element tmp_94;
     Goldilocks3::add(tmp_94, tmp_93, (Goldilocks3::Element &)*params.challenges[2]);
     Goldilocks3::Element tmp_148;
     Goldilocks3::mul(tmp_148, tmp_146, tmp_94);
     Goldilocks::Element tmp_149;
     Goldilocks::copy(tmp_149, params.pols[4 + i*12]);
     Goldilocks3::Element tmp_95;
     Goldilocks3::mul(tmp_95, Goldilocks::fromU64(8312008622371998338ULL), (Goldilocks3::Element &)*params.challenges[3]);
     Goldilocks3::Element tmp_96;
     Goldilocks3::mul(tmp_96, (Goldilocks::Element &)*params.x_n[i], tmp_95);
     Goldilocks3::Element tmp_97;
     Goldilocks3::add(tmp_97, tmp_149, tmp_96);
     Goldilocks3::Element tmp_98;
     Goldilocks3::add(tmp_98, tmp_97, (Goldilocks3::Element &)*params.challenges[2]);
     Goldilocks3::mul((Goldilocks3::Element &)(params.pols[50331651 + i*15]), tmp_148, tmp_98);
     Goldilocks::Element tmp_150;
     Goldilocks::copy(tmp_150,  params.pConstPols->getElement(4,i));
     Goldilocks3::Element tmp_99;
     Goldilocks3::mul(tmp_99, tmp_150, (Goldilocks3::Element &)*params.challenges[3]);
     Goldilocks3::Element tmp_100;
     Goldilocks3::add(tmp_100, tmp_141, tmp_99);
     Goldilocks3::Element tmp_151;
     Goldilocks3::add(tmp_151, tmp_100, (Goldilocks3::Element &)*params.challenges[2]);
     Goldilocks::Element tmp_152;
     Goldilocks::copy(tmp_152,  params.pConstPols->getElement(5,i));
     Goldilocks3::Element tmp_101;
     Goldilocks3::mul(tmp_101, tmp_152, (Goldilocks3::Element &)*params.challenges[3]);
     Goldilocks3::Element tmp_102;
     Goldilocks3::add(tmp_102, tmp_143, tmp_101);
     Goldilocks3::Element tmp_103;
     Goldilocks3::add(tmp_103, tmp_102, (Goldilocks3::Element &)*params.challenges[2]);
     Goldilocks3::Element tmp_153;
     Goldilocks3::mul(tmp_153, tmp_151, tmp_103);
     Goldilocks::Element tmp_154;
     Goldilocks::copy(tmp_154,  params.pConstPols->getElement(6,i));
     Goldilocks3::Element tmp_104;
     Goldilocks3::mul(tmp_104, tmp_154, (Goldilocks3::Element &)*params.challenges[3]);
     Goldilocks3::Element tmp_105;
     Goldilocks3::add(tmp_105, tmp_145, tmp_104);
     Goldilocks3::Element tmp_106;
     Goldilocks3::add(tmp_106, tmp_105, (Goldilocks3::Element &)*params.challenges[2]);
     Goldilocks3::Element tmp_155;
     Goldilocks3::mul(tmp_155, tmp_153, tmp_106);
     Goldilocks::Element tmp_156;
     Goldilocks::copy(tmp_156,  params.pConstPols->getElement(7,i));
     Goldilocks3::Element tmp_107;
     Goldilocks3::mul(tmp_107, tmp_156, (Goldilocks3::Element &)*params.challenges[3]);
     Goldilocks3::Element tmp_108;
     Goldilocks3::add(tmp_108, tmp_147, tmp_107);
     Goldilocks3::Element tmp_109;
     Goldilocks3::add(tmp_109, tmp_108, (Goldilocks3::Element &)*params.challenges[2]);
     Goldilocks3::Element tmp_157;
     Goldilocks3::mul(tmp_157, tmp_155, tmp_109);
     Goldilocks::Element tmp_158;
     Goldilocks::copy(tmp_158,  params.pConstPols->getElement(8,i));
     Goldilocks3::Element tmp_110;
     Goldilocks3::mul(tmp_110, tmp_158, (Goldilocks3::Element &)*params.challenges[3]);
     Goldilocks3::Element tmp_111;
     Goldilocks3::add(tmp_111, tmp_149, tmp_110);
     Goldilocks3::Element tmp_112;
     Goldilocks3::add(tmp_112, tmp_111, (Goldilocks3::Element &)*params.challenges[2]);
     Goldilocks3::mul((Goldilocks3::Element &)(params.pols[50331654 + i*15]), tmp_157, tmp_112);
     Goldilocks::Element tmp_159;
     Goldilocks::copy(tmp_159, params.pols[5 + i*12]);
     Goldilocks3::Element tmp_113;
     Goldilocks3::mul(tmp_113, Goldilocks::fromU64(7781028390488215464ULL), (Goldilocks3::Element &)*params.challenges[3]);
     Goldilocks3::Element tmp_114;
     Goldilocks3::mul(tmp_114, (Goldilocks::Element &)*params.x_n[i], tmp_113);
     Goldilocks3::Element tmp_115;
     Goldilocks3::add(tmp_115, tmp_159, tmp_114);
     Goldilocks3::Element tmp_116;
     Goldilocks3::add(tmp_116, tmp_115, (Goldilocks3::Element &)*params.challenges[2]);
     Goldilocks3::Element tmp_160;
     Goldilocks3::mul(tmp_160, (Goldilocks3::Element &)(params.pols[50331651 + i*15]), tmp_116);
     Goldilocks::Element tmp_161;
     Goldilocks::copy(tmp_161, params.pols[6 + i*12]);
     Goldilocks3::Element tmp_117;
     Goldilocks3::mul(tmp_117, Goldilocks::fromU64(11302600489504509467ULL), (Goldilocks3::Element &)*params.challenges[3]);
     Goldilocks3::Element tmp_118;
     Goldilocks3::mul(tmp_118, (Goldilocks::Element &)*params.x_n[i], tmp_117);
     Goldilocks3::Element tmp_119;
     Goldilocks3::add(tmp_119, tmp_161, tmp_118);
     Goldilocks3::Element tmp_120;
     Goldilocks3::add(tmp_120, tmp_119, (Goldilocks3::Element &)*params.challenges[2]);
     Goldilocks3::Element tmp_162;
     Goldilocks3::mul(tmp_162, tmp_160, tmp_120);
     Goldilocks::Element tmp_163;
     Goldilocks::copy(tmp_163, params.pols[7 + i*12]);
     Goldilocks3::Element tmp_121;
     Goldilocks3::mul(tmp_121, Goldilocks::fromU64(4549350404001778198ULL), (Goldilocks3::Element &)*params.challenges[3]);
     Goldilocks3::Element tmp_122;
     Goldilocks3::mul(tmp_122, (Goldilocks::Element &)*params.x_n[i], tmp_121);
     Goldilocks3::Element tmp_123;
     Goldilocks3::add(tmp_123, tmp_163, tmp_122);
     Goldilocks3::Element tmp_124;
     Goldilocks3::add(tmp_124, tmp_123, (Goldilocks3::Element &)*params.challenges[2]);
     Goldilocks3::Element tmp_164;
     Goldilocks3::mul(tmp_164, tmp_162, tmp_124);
     Goldilocks::Element tmp_165;
     Goldilocks::copy(tmp_165, params.pols[8 + i*12]);
     Goldilocks3::Element tmp_125;
     Goldilocks3::mul(tmp_125, Goldilocks::fromU64(3688660304411827445ULL), (Goldilocks3::Element &)*params.challenges[3]);
     Goldilocks3::Element tmp_126;
     Goldilocks3::mul(tmp_126, (Goldilocks::Element &)*params.x_n[i], tmp_125);
     Goldilocks3::Element tmp_127;
     Goldilocks3::add(tmp_127, tmp_165, tmp_126);
     Goldilocks3::Element tmp_128;
     Goldilocks3::add(tmp_128, tmp_127, (Goldilocks3::Element &)*params.challenges[2]);
     Goldilocks3::mul((Goldilocks3::Element &)(params.pols[50331657 + i*15]), tmp_164, tmp_128);
     Goldilocks::Element tmp_166;
     Goldilocks::copy(tmp_166,  params.pConstPols->getElement(9,i));
     Goldilocks3::Element tmp_129;
     Goldilocks3::mul(tmp_129, tmp_166, (Goldilocks3::Element &)*params.challenges[3]);
     Goldilocks3::Element tmp_130;
     Goldilocks3::add(tmp_130, tmp_159, tmp_129);
     Goldilocks3::Element tmp_131;
     Goldilocks3::add(tmp_131, tmp_130, (Goldilocks3::Element &)*params.challenges[2]);
     Goldilocks3::Element tmp_167;
     Goldilocks3::mul(tmp_167, (Goldilocks3::Element &)(params.pols[50331654 + i*15]), tmp_131);
     Goldilocks::Element tmp_168;
     Goldilocks::copy(tmp_168,  params.pConstPols->getElement(10,i));
     Goldilocks3::Element tmp_132;
     Goldilocks3::mul(tmp_132, tmp_168, (Goldilocks3::Element &)*params.challenges[3]);
     Goldilocks3::Element tmp_133;
     Goldilocks3::add(tmp_133, tmp_161, tmp_132);
     Goldilocks3::Element tmp_134;
     Goldilocks3::add(tmp_134, tmp_133, (Goldilocks3::Element &)*params.challenges[2]);
     Goldilocks3::Element tmp_169;
     Goldilocks3::mul(tmp_169, tmp_167, tmp_134);
     Goldilocks::Element tmp_170;
     Goldilocks::copy(tmp_170,  params.pConstPols->getElement(11,i));
     Goldilocks3::Element tmp_135;
     Goldilocks3::mul(tmp_135, tmp_170, (Goldilocks3::Element &)*params.challenges[3]);
     Goldilocks3::Element tmp_136;
     Goldilocks3::add(tmp_136, tmp_163, tmp_135);
     Goldilocks3::Element tmp_137;
     Goldilocks3::add(tmp_137, tmp_136, (Goldilocks3::Element &)*params.challenges[2]);
     Goldilocks3::Element tmp_171;
     Goldilocks3::mul(tmp_171, tmp_169, tmp_137);
     Goldilocks::Element tmp_172;
     Goldilocks::copy(tmp_172,  params.pConstPols->getElement(12,i));
     Goldilocks3::Element tmp_138;
     Goldilocks3::mul(tmp_138, tmp_172, (Goldilocks3::Element &)*params.challenges[3]);
     Goldilocks3::Element tmp_139;
     Goldilocks3::add(tmp_139, tmp_165, tmp_138);
     Goldilocks3::Element tmp_140;
     Goldilocks3::add(tmp_140, tmp_139, (Goldilocks3::Element &)*params.challenges[2]);
     Goldilocks3::mul((Goldilocks3::Element &)(params.pols[50331660 + i*15]), tmp_171, tmp_140);
}

void StarkRecursiveFSteps::step3_last(StepsParams &params, uint64_t i) {
     Goldilocks::Element tmp_141;
     Goldilocks::copy(tmp_141, params.pols[0 + i*12]);
     Goldilocks3::Element tmp_81;
     Goldilocks3::mul(tmp_81, (Goldilocks::Element &)*params.x_n[i], (Goldilocks3::Element &)*params.challenges[3]);
     Goldilocks3::Element tmp_82;
     Goldilocks3::add(tmp_82, tmp_141, tmp_81);
     Goldilocks3::Element tmp_142;
     Goldilocks3::add(tmp_142, tmp_82, (Goldilocks3::Element &)*params.challenges[2]);
     Goldilocks::Element tmp_143;
     Goldilocks::copy(tmp_143, params.pols[1 + i*12]);
     Goldilocks3::Element tmp_83;
     Goldilocks3::mul(tmp_83, Goldilocks::fromU64(12275445934081160404ULL), (Goldilocks3::Element &)*params.challenges[3]);
     Goldilocks3::Element tmp_84;
     Goldilocks3::mul(tmp_84, (Goldilocks::Element &)*params.x_n[i], tmp_83);
     Goldilocks3::Element tmp_85;
     Goldilocks3::add(tmp_85, tmp_143, tmp_84);
     Goldilocks3::Element tmp_86;
     Goldilocks3::add(tmp_86, tmp_85, (Goldilocks3::Element &)*params.challenges[2]);
     Goldilocks3::Element tmp_144;
     Goldilocks3::mul(tmp_144, tmp_142, tmp_86);
     Goldilocks::Element tmp_145;
     Goldilocks::copy(tmp_145, params.pols[2 + i*12]);
     Goldilocks3::Element tmp_87;
     Goldilocks3::mul(tmp_87, Goldilocks::fromU64(4756475762779100925ULL), (Goldilocks3::Element &)*params.challenges[3]);
     Goldilocks3::Element tmp_88;
     Goldilocks3::mul(tmp_88, (Goldilocks::Element &)*params.x_n[i], tmp_87);
     Goldilocks3::Element tmp_89;
     Goldilocks3::add(tmp_89, tmp_145, tmp_88);
     Goldilocks3::Element tmp_90;
     Goldilocks3::add(tmp_90, tmp_89, (Goldilocks3::Element &)*params.challenges[2]);
     Goldilocks3::Element tmp_146;
     Goldilocks3::mul(tmp_146, tmp_144, tmp_90);
     Goldilocks::Element tmp_147;
     Goldilocks::copy(tmp_147, params.pols[3 + i*12]);
     Goldilocks3::Element tmp_91;
     Goldilocks3::mul(tmp_91, Goldilocks::fromU64(1279992132519201448ULL), (Goldilocks3::Element &)*params.challenges[3]);
     Goldilocks3::Element tmp_92;
     Goldilocks3::mul(tmp_92, (Goldilocks::Element &)*params.x_n[i], tmp_91);
     Goldilocks3::Element tmp_93;
     Goldilocks3::add(tmp_93, tmp_147, tmp_92);
     Goldilocks3::Element tmp_94;
     Goldilocks3::add(tmp_94, tmp_93, (Goldilocks3::Element &)*params.challenges[2]);
     Goldilocks3::Element tmp_148;
     Goldilocks3::mul(tmp_148, tmp_146, tmp_94);
     Goldilocks::Element tmp_149;
     Goldilocks::copy(tmp_149, params.pols[4 + i*12]);
     Goldilocks3::Element tmp_95;
     Goldilocks3::mul(tmp_95, Goldilocks::fromU64(8312008622371998338ULL), (Goldilocks3::Element &)*params.challenges[3]);
     Goldilocks3::Element tmp_96;
     Goldilocks3::mul(tmp_96, (Goldilocks::Element &)*params.x_n[i], tmp_95);
     Goldilocks3::Element tmp_97;
     Goldilocks3::add(tmp_97, tmp_149, tmp_96);
     Goldilocks3::Element tmp_98;
     Goldilocks3::add(tmp_98, tmp_97, (Goldilocks3::Element &)*params.challenges[2]);
     Goldilocks3::mul((Goldilocks3::Element &)(params.pols[50331651 + i*15]), tmp_148, tmp_98);
     Goldilocks::Element tmp_150;
     Goldilocks::copy(tmp_150,  params.pConstPols->getElement(4,i));
     Goldilocks3::Element tmp_99;
     Goldilocks3::mul(tmp_99, tmp_150, (Goldilocks3::Element &)*params.challenges[3]);
     Goldilocks3::Element tmp_100;
     Goldilocks3::add(tmp_100, tmp_141, tmp_99);
     Goldilocks3::Element tmp_151;
     Goldilocks3::add(tmp_151, tmp_100, (Goldilocks3::Element &)*params.challenges[2]);
     Goldilocks::Element tmp_152;
     Goldilocks::copy(tmp_152,  params.pConstPols->getElement(5,i));
     Goldilocks3::Element tmp_101;
     Goldilocks3::mul(tmp_101, tmp_152, (Goldilocks3::Element &)*params.challenges[3]);
     Goldilocks3::Element tmp_102;
     Goldilocks3::add(tmp_102, tmp_143, tmp_101);
     Goldilocks3::Element tmp_103;
     Goldilocks3::add(tmp_103, tmp_102, (Goldilocks3::Element &)*params.challenges[2]);
     Goldilocks3::Element tmp_153;
     Goldilocks3::mul(tmp_153, tmp_151, tmp_103);
     Goldilocks::Element tmp_154;
     Goldilocks::copy(tmp_154,  params.pConstPols->getElement(6,i));
     Goldilocks3::Element tmp_104;
     Goldilocks3::mul(tmp_104, tmp_154, (Goldilocks3::Element &)*params.challenges[3]);
     Goldilocks3::Element tmp_105;
     Goldilocks3::add(tmp_105, tmp_145, tmp_104);
     Goldilocks3::Element tmp_106;
     Goldilocks3::add(tmp_106, tmp_105, (Goldilocks3::Element &)*params.challenges[2]);
     Goldilocks3::Element tmp_155;
     Goldilocks3::mul(tmp_155, tmp_153, tmp_106);
     Goldilocks::Element tmp_156;
     Goldilocks::copy(tmp_156,  params.pConstPols->getElement(7,i));
     Goldilocks3::Element tmp_107;
     Goldilocks3::mul(tmp_107, tmp_156, (Goldilocks3::Element &)*params.challenges[3]);
     Goldilocks3::Element tmp_108;
     Goldilocks3::add(tmp_108, tmp_147, tmp_107);
     Goldilocks3::Element tmp_109;
     Goldilocks3::add(tmp_109, tmp_108, (Goldilocks3::Element &)*params.challenges[2]);
     Goldilocks3::Element tmp_157;
     Goldilocks3::mul(tmp_157, tmp_155, tmp_109);
     Goldilocks::Element tmp_158;
     Goldilocks::copy(tmp_158,  params.pConstPols->getElement(8,i));
     Goldilocks3::Element tmp_110;
     Goldilocks3::mul(tmp_110, tmp_158, (Goldilocks3::Element &)*params.challenges[3]);
     Goldilocks3::Element tmp_111;
     Goldilocks3::add(tmp_111, tmp_149, tmp_110);
     Goldilocks3::Element tmp_112;
     Goldilocks3::add(tmp_112, tmp_111, (Goldilocks3::Element &)*params.challenges[2]);
     Goldilocks3::mul((Goldilocks3::Element &)(params.pols[50331654 + i*15]), tmp_157, tmp_112);
     Goldilocks::Element tmp_159;
     Goldilocks::copy(tmp_159, params.pols[5 + i*12]);
     Goldilocks3::Element tmp_113;
     Goldilocks3::mul(tmp_113, Goldilocks::fromU64(7781028390488215464ULL), (Goldilocks3::Element &)*params.challenges[3]);
     Goldilocks3::Element tmp_114;
     Goldilocks3::mul(tmp_114, (Goldilocks::Element &)*params.x_n[i], tmp_113);
     Goldilocks3::Element tmp_115;
     Goldilocks3::add(tmp_115, tmp_159, tmp_114);
     Goldilocks3::Element tmp_116;
     Goldilocks3::add(tmp_116, tmp_115, (Goldilocks3::Element &)*params.challenges[2]);
     Goldilocks3::Element tmp_160;
     Goldilocks3::mul(tmp_160, (Goldilocks3::Element &)(params.pols[50331651 + i*15]), tmp_116);
     Goldilocks::Element tmp_161;
     Goldilocks::copy(tmp_161, params.pols[6 + i*12]);
     Goldilocks3::Element tmp_117;
     Goldilocks3::mul(tmp_117, Goldilocks::fromU64(11302600489504509467ULL), (Goldilocks3::Element &)*params.challenges[3]);
     Goldilocks3::Element tmp_118;
     Goldilocks3::mul(tmp_118, (Goldilocks::Element &)*params.x_n[i], tmp_117);
     Goldilocks3::Element tmp_119;
     Goldilocks3::add(tmp_119, tmp_161, tmp_118);
     Goldilocks3::Element tmp_120;
     Goldilocks3::add(tmp_120, tmp_119, (Goldilocks3::Element &)*params.challenges[2]);
     Goldilocks3::Element tmp_162;
     Goldilocks3::mul(tmp_162, tmp_160, tmp_120);
     Goldilocks::Element tmp_163;
     Goldilocks::copy(tmp_163, params.pols[7 + i*12]);
     Goldilocks3::Element tmp_121;
     Goldilocks3::mul(tmp_121, Goldilocks::fromU64(4549350404001778198ULL), (Goldilocks3::Element &)*params.challenges[3]);
     Goldilocks3::Element tmp_122;
     Goldilocks3::mul(tmp_122, (Goldilocks::Element &)*params.x_n[i], tmp_121);
     Goldilocks3::Element tmp_123;
     Goldilocks3::add(tmp_123, tmp_163, tmp_122);
     Goldilocks3::Element tmp_124;
     Goldilocks3::add(tmp_124, tmp_123, (Goldilocks3::Element &)*params.challenges[2]);
     Goldilocks3::Element tmp_164;
     Goldilocks3::mul(tmp_164, tmp_162, tmp_124);
     Goldilocks::Element tmp_165;
     Goldilocks::copy(tmp_165, params.pols[8 + i*12]);
     Goldilocks3::Element tmp_125;
     Goldilocks3::mul(tmp_125, Goldilocks::fromU64(3688660304411827445ULL), (Goldilocks3::Element &)*params.challenges[3]);
     Goldilocks3::Element tmp_126;
     Goldilocks3::mul(tmp_126, (Goldilocks::Element &)*params.x_n[i], tmp_125);
     Goldilocks3::Element tmp_127;
     Goldilocks3::add(tmp_127, tmp_165, tmp_126);
     Goldilocks3::Element tmp_128;
     Goldilocks3::add(tmp_128, tmp_127, (Goldilocks3::Element &)*params.challenges[2]);
     Goldilocks3::mul((Goldilocks3::Element &)(params.pols[50331657 + i*15]), tmp_164, tmp_128);
     Goldilocks::Element tmp_166;
     Goldilocks::copy(tmp_166,  params.pConstPols->getElement(9,i));
     Goldilocks3::Element tmp_129;
     Goldilocks3::mul(tmp_129, tmp_166, (Goldilocks3::Element &)*params.challenges[3]);
     Goldilocks3::Element tmp_130;
     Goldilocks3::add(tmp_130, tmp_159, tmp_129);
     Goldilocks3::Element tmp_131;
     Goldilocks3::add(tmp_131, tmp_130, (Goldilocks3::Element &)*params.challenges[2]);
     Goldilocks3::Element tmp_167;
     Goldilocks3::mul(tmp_167, (Goldilocks3::Element &)(params.pols[50331654 + i*15]), tmp_131);
     Goldilocks::Element tmp_168;
     Goldilocks::copy(tmp_168,  params.pConstPols->getElement(10,i));
     Goldilocks3::Element tmp_132;
     Goldilocks3::mul(tmp_132, tmp_168, (Goldilocks3::Element &)*params.challenges[3]);
     Goldilocks3::Element tmp_133;
     Goldilocks3::add(tmp_133, tmp_161, tmp_132);
     Goldilocks3::Element tmp_134;
     Goldilocks3::add(tmp_134, tmp_133, (Goldilocks3::Element &)*params.challenges[2]);
     Goldilocks3::Element tmp_169;
     Goldilocks3::mul(tmp_169, tmp_167, tmp_134);
     Goldilocks::Element tmp_170;
     Goldilocks::copy(tmp_170,  params.pConstPols->getElement(11,i));
     Goldilocks3::Element tmp_135;
     Goldilocks3::mul(tmp_135, tmp_170, (Goldilocks3::Element &)*params.challenges[3]);
     Goldilocks3::Element tmp_136;
     Goldilocks3::add(tmp_136, tmp_163, tmp_135);
     Goldilocks3::Element tmp_137;
     Goldilocks3::add(tmp_137, tmp_136, (Goldilocks3::Element &)*params.challenges[2]);
     Goldilocks3::Element tmp_171;
     Goldilocks3::mul(tmp_171, tmp_169, tmp_137);
     Goldilocks::Element tmp_172;
     Goldilocks::copy(tmp_172,  params.pConstPols->getElement(12,i));
     Goldilocks3::Element tmp_138;
     Goldilocks3::mul(tmp_138, tmp_172, (Goldilocks3::Element &)*params.challenges[3]);
     Goldilocks3::Element tmp_139;
     Goldilocks3::add(tmp_139, tmp_165, tmp_138);
     Goldilocks3::Element tmp_140;
     Goldilocks3::add(tmp_140, tmp_139, (Goldilocks3::Element &)*params.challenges[2]);
     Goldilocks3::mul((Goldilocks3::Element &)(params.pols[50331660 + i*15]), tmp_171, tmp_140);
}

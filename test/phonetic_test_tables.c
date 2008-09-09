/*
 * Copyright © 2008  Red Hat, Inc. All rights reserved.
 * Copyright © 2008  Ding-Yi Chen <dchen at redhat dot com>
 *
 * This file is part of the libUnihan Project.
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this program; if not, write to the
 * Free Software Foundation, Inc., 59 Temple Place, Suite 330,
 * Boston, MA  02111-1307  USA
 */ 

const char *PINYIN_COMBINATION_TABLES_ALWAYS[]={
    "BA",
    "BO",
    "BAI",
    "BEI",
    "BAO",
    "BAN",
    "BEN",
    "BANG",
    "BENG",
    "BI",
    "BIÊ",
    "BIAO",
    "BIAN",
    "BIN",
    "BING",
    "BU",
    "PA",
    "PO",
    "PAI",
    "PEI",
    "PAO",
    "POU",
    "PAN",
    "PEN",
    "PANG",
    "PENG",
    "PI",
    "PIÊ",
    "PIAO",
    "PIAN",
    "PIN",
    "PING",
    "PU",
    "MA",
    "MO",
    "ME",
    "MAI",
    "MEI",
    "MAO",
    "MOU",
    "MAN",
    "MEN",
    "MANG",
    "MENG",
    "MI",
    "MIÊ",
    "MIAO",
    "MIU",
    "MIAN",
    "MIN",
    "MING",
    "MU",
    "FA",
    "FO",
    "FEI",
    "FOU",
    "FAN",
    "FEN",
    "FANG",
    "FENG",
    "FIAO",
    "FU",
    "FONG",
    "DA",
    "DE",
    "DAI",
    "DEI",
    "DAO",
    "DOU",
    "DAN",
    "DEN",
    "DANG",
    "DENG",
    "DI",
    "DIA",
    "DIÊ",
    "DIAO",
    "DIU",
    "DIAN",
    "DING",
    "DU",
    "DUO",
    "DUI",
    "DUAN",
    "DUN",
    "DONG",
    "TA",
    "TE",
    "TAI",
    "TAO",
    "TOU",
    "TAN",
    "TANG",
    "TENG",
    "TI",
    "TIÊ",
    "TIAO",
    "TIAN",
    "TING",
    "TU",
    "TUO",
    "TUI",
    "TUAN",
    "TUN",
    "TONG",
    "NA",
    "NE",
    "NAI",
    "NEI",
    "NAO",
    "NOU",
    "NAN",
    "NEN",
    "NANG",
    "NENG",
    "NI",
    "NIA",
    "NIÊ",
    "NIAO",
    "NIU",
    "NIAN",
    "NIN",
    "NIANG",
    "NING",
    "NU",
    "NUO",
    "NUAN",
    "NUN",
    "NONG",
    "NÜ",
    "NÜÊ",
    "LA",
    "LO",
    "LE",
    "LAI",
    "LEI",
    "LAO",
    "LOU",
    "LAN",
    "LANG",
    "LENG",
    "LI",
    "LIA",
    "LIÊ",
    "LIAO",
    "LIU",
    "LIAN",
    "LIN",
    "LIANG",
    "LING",
    "LU",
    "LUO",
    "LUAN",
    "LUN",
    "LONG",
    "LÜ",
    "LÜÊ",
    "LÜAN",
    "GA",
    "GE",
    "GAI",
    "GEI",
    "GAO",
    "GOU",
    "GAN",
    "GEN",
    "GANG",
    "GENG",
    "GU",
    "GUA",
    "GUO",
    "GUAI",
    "GUI",
    "GUAN",
    "GUN",
    "GUANG",
    "GONG",
    "KA",
    "KE",
    "KAI",
    "KAO",
    "KOU",
    "KAN",
    "KEN",
    "KANG",
    "KENG",
    "KU",
    "KUA",
    "KUO",
    "KUAI",
    "KUI",
    "KUAN",
    "KUN",
    "KUANG",
    "KONG",
    "HA",
    "HE",
    "HAI",
    "HEI",
    "HAO",
    "HOU",
    "HAN",
    "HEN",
    "HANG",
    "HENG",
    "HU",
    "HUA",
    "HUO",
    "HUAI",
    "HUI",
    "HUAN",
    "HUN",
    "HUANG",
    "HONG",
    "JI",
    "JIA",
    "JIÊ",
    "JIAO",
    "JIU",
    "JIAN",
    "JIN",
    "JIANG",
    "JING",
    "JÜ",
    "JÜÊ",
    "JÜAN",
    "JÜN",
    "JIONG",
    "QI",
    "QIA",
    "QIÊ",
    "QIAO",
    "QIU",
    "QIAN",
    "QIN",
    "QIANG",
    "QING",
    "QÜ",
    "QÜÊ",
    "QÜAN",
    "QÜN",
    "QIONG",
    "XI",
    "XIA",
    "XIÊ",
    "XIAO",
    "XIU",
    "XIAN",
    "XIN",
    "XIANG",
    "XING",
    "XÜ",
    "XÜÊ",
    "XÜAN",
    "XÜN",
    "XIONG",
    "ZHI",
    "ZHA",
    "ZHE",
    "ZHAI",
    "ZHEI",
    "ZHAO",
    "ZHOU",
    "ZHAN",
    "ZHEN",
    "ZHANG",
    "ZHENG",
    "ZHU",
    "ZHUA",
    "ZHUO",
    "ZHUAI",
    "ZHUI",
    "ZHUAN",
    "ZHUN",
    "ZHUANG",
    "ZHONG",
    "CHI",
    "CHA",
    "CHE",
    "CHAI",
    "CHAO",
    "CHOU",
    "CHAN",
    "CHEN",
    "CHANG",
    "CHENG",
    "CHU",
    "CHUA",
    "CHUO",
    "CHUAI",
    "CHUI",
    "CHUAN",
    "CHUN",
    "CHUANG",
    "CHONG",
    "SHI",
    "SHA",
    "SHE",
    "SHAI",
    "SHEI",
    "SHAO",
    "SHOU",
    "SHAN",
    "SHEN",
    "SHANG",
    "SHENG",
    "SHU",
    "SHUA",
    "SHUO",
    "SHUAI",
    "SHUI",
    "SHUAN",
    "SHUN",
    "SHUANG",
    "RI",
    "RE",
    "RAO",
    "ROU",
    "RAN",
    "REN",
    "RANG",
    "RENG",
    "RU",
    "RUO",
    "RUI",
    "RUAN",
    "RUN",
    "RONG",
    "ZI",
    "ZA",
    "ZE",
    "ZAI",
    "ZEI",
    "ZAO",
    "ZOU",
    "ZAN",
    "ZEN",
    "ZANG",
    "ZENG",
    "ZU",
    "ZUO",
    "ZUI",
    "ZUAN",
    "ZUN",
    "ZONG",
    "CI",
    "CA",
    "CE",
    "CAI",
    "CAO",
    "COU",
    "CAN",
    "CEN",
    "CANG",
    "CENG",
    "CU",
    "CUO",
    "CUI",
    "CUAN",
    "CUN",
    "CONG",
    "SI",
    "SA",
    "SE",
    "SAI",
    "SEI",
    "SAO",
    "SOU",
    "SAN",
    "SEN",
    "SANG",
    "SENG",
    "SU",
    "SUO",
    "SUI",
    "SUAN",
    "SUN",
    "SONG",
    "A",
    "O",
    "E",
    "Ê",
    "AI",
    "EI",
    "AO",
    "OU",
    "AN",
    "EN",
    "ANG",
    "ENG",
    "ER",
    "YI",
    "YA",
    "YO",
    "YE",
    "YAI",
    "YAO",
    "YÜ",
    "YAN",
    "YIN",
    "YANG",
    "YING",
    "WU",
    "WA",
    "WO",
    "WAI",
    "WI",
    "WAN",
    "WN",
    "WANG",
    "WENG",
    "YÜ",
    "YÜÊ",
    "YÜAN",
    "YÜN",
    "YONG",
    NULL
};
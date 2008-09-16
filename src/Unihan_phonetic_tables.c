/** 
 * @file Unihan_Phonetic_Table.c
 *
 */

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

#include <stdlib.h>

const char *ZHUYIN_COMBINATION_TABLES[]={
    "ㄅㄚ",
    "ㄅㄛ",
    "ㄅㄞ",
    "ㄅㄟ",
    "ㄅㄠ",
    "ㄅㄢ",
    "ㄅㄣ",
    "ㄅㄤ",
    "ㄅㄥ",
    "ㄅㄧ",
    "ㄅㄧㄝ",
    "ㄅㄧㄠ",
    "ㄅㄧㄢ",
    "ㄅㄧㄣ",
    "ㄅㄧㄥ",
    "ㄅㄨ",
    "ㄆㄚ",
    "ㄆㄛ",
    "ㄆㄞ",
    "ㄆㄟ",
    "ㄆㄠ",
    "ㄆㄡ",
    "ㄆㄢ",
    "ㄆㄣ",
    "ㄆㄤ",
    "ㄆㄥ",
    "ㄆㄧ",
    "ㄆㄧㄝ",
    "ㄆㄧㄠ",
    "ㄆㄧㄢ",
    "ㄆㄧㄣ",
    "ㄆㄧㄥ",
    "ㄆㄨ",
    "ㄇㄚ",
    "ㄇㄛ",
    "ㄇㄜ",
    "ㄇㄞ",
    "ㄇㄟ",
    "ㄇㄠ",
    "ㄇㄡ",
    "ㄇㄢ",
    "ㄇㄣ",
    "ㄇㄤ",
    "ㄇㄥ",
    "ㄇㄧ",
    "ㄇㄧㄝ",
    "ㄇㄧㄠ",
    "ㄇㄧㄡ",
    "ㄇㄧㄢ",
    "ㄇㄧㄣ",
    "ㄇㄧㄥ",
    "ㄇㄨ",
    "ㄈㄚ",
    "ㄈㄛ",
    "ㄈㄟ",
    "ㄈㄡ",
    "ㄈㄢ",
    "ㄈㄣ",
    "ㄈㄤ",
    "ㄈㄥ",
    "ㄈㄧㄠ",
    "ㄈㄨ",
    "ㄈㄨㄥ",
    "ㄉㄚ",
    "ㄉㄜ",
    "ㄉㄞ",
    "ㄉㄟ",
    "ㄉㄠ",
    "ㄉㄡ",
    "ㄉㄢ",
    "ㄉㄣ",
    "ㄉㄤ",
    "ㄉㄥ",
    "ㄉㄧ",
    "ㄉㄧㄚ",
    "ㄉㄧㄝ",
    "ㄉㄧㄠ",
    "ㄉㄧㄡ",
    "ㄉㄧㄢ",
    "ㄉㄧㄥ",
    "ㄉㄨ",
    "ㄉㄨㄛ",
    "ㄉㄨㄟ",
    "ㄉㄨㄢ",
    "ㄉㄨㄣ",
    "ㄉㄨㄥ",
    "ㄊㄚ",
    "ㄊㄜ",
    "ㄊㄞ",
    "ㄊㄠ",
    "ㄊㄡ",
    "ㄊㄢ",
    "ㄊㄤ",
    "ㄊㄥ",
    "ㄊㄧ",
    "ㄊㄧㄝ",
    "ㄊㄧㄠ",
    "ㄊㄧㄢ",
    "ㄊㄧㄥ",
    "ㄊㄨ",
    "ㄊㄨㄛ",
    "ㄊㄨㄟ",
    "ㄊㄨㄢ",
    "ㄊㄨㄣ",
    "ㄊㄨㄥ",
    "ㄋㄚ",
    "ㄋㄜ",
    "ㄋㄞ",
    "ㄋㄟ",
    "ㄋㄠ",
    "ㄋㄡ",
    "ㄋㄢ",
    "ㄋㄣ",
    "ㄋㄤ",
    "ㄋㄥ",
    "ㄋㄧ",
    "ㄋㄧㄚ",
    "ㄋㄧㄝ",
    "ㄋㄧㄠ",
    "ㄋㄧㄡ",
    "ㄋㄧㄢ",
    "ㄋㄧㄣ",
    "ㄋㄧㄤ",
    "ㄋㄧㄥ",
    "ㄋㄨ",
    "ㄋㄨㄛ",
    "ㄋㄨㄢ",
    "ㄋㄨㄣ",
    "ㄋㄨㄥ",
    "ㄋㄩ",
    "ㄋㄩㄝ",
    "ㄌㄚ",
    "ㄌㄛ",
    "ㄌㄜ",
    "ㄌㄞ",
    "ㄌㄟ",
    "ㄌㄠ",
    "ㄌㄡ",
    "ㄌㄢ",
    "ㄌㄤ",
    "ㄌㄥ",
    "ㄌㄧ",
    "ㄌㄧㄚ",
    "ㄌㄧㄝ",
    "ㄌㄧㄠ",
    "ㄌㄧㄡ",
    "ㄌㄧㄢ",
    "ㄌㄧㄣ",
    "ㄌㄧㄤ",
    "ㄌㄧㄥ",
    "ㄌㄨ",
    "ㄌㄨㄛ",
    "ㄌㄨㄢ",
    "ㄌㄨㄣ",
    "ㄌㄨㄥ",
    "ㄌㄩ",
    "ㄌㄩㄝ",
    "ㄌㄩㄢ",
    "ㄍㄚ",
    "ㄍㄜ",
    "ㄍㄞ",
    "ㄍㄟ",
    "ㄍㄠ",
    "ㄍㄡ",
    "ㄍㄢ",
    "ㄍㄣ",
    "ㄍㄤ",
    "ㄍㄥ",
    "ㄍㄨ",
    "ㄍㄨㄚ",
    "ㄍㄨㄛ",
    "ㄍㄨㄞ",
    "ㄍㄨㄟ",
    "ㄍㄨㄢ",
    "ㄍㄨㄣ",
    "ㄍㄨㄤ",
    "ㄍㄨㄥ",
    "ㄎㄚ",
    "ㄎㄜ",
    "ㄎㄞ",
    "ㄎㄠ",
    "ㄎㄡ",
    "ㄎㄢ",
    "ㄎㄣ",
    "ㄎㄤ",
    "ㄎㄥ",
    "ㄎㄨ",
    "ㄎㄨㄚ",
    "ㄎㄨㄛ",
    "ㄎㄨㄞ",
    "ㄎㄨㄟ",
    "ㄎㄨㄢ",
    "ㄎㄨㄣ",
    "ㄎㄨㄤ",
    "ㄎㄨㄥ",
    "ㄏㄚ",
    "ㄏㄜ",
    "ㄏㄞ",
    "ㄏㄟ",
    "ㄏㄠ",
    "ㄏㄡ",
    "ㄏㄢ",
    "ㄏㄣ",
    "ㄏㄤ",
    "ㄏㄥ",
    "ㄏㄨ",
    "ㄏㄨㄚ",
    "ㄏㄨㄛ",
    "ㄏㄨㄞ",
    "ㄏㄨㄟ",
    "ㄏㄨㄢ",
    "ㄏㄨㄣ",
    "ㄏㄨㄤ",
    "ㄏㄨㄥ",
    "ㄐㄧ",
    "ㄐㄧㄚ",
    "ㄐㄧㄝ",
    "ㄐㄧㄠ",
    "ㄐㄧㄡ",
    "ㄐㄧㄢ",
    "ㄐㄧㄣ",
    "ㄐㄧㄤ",
    "ㄐㄧㄥ",
    "ㄐㄩ",
    "ㄐㄩㄝ",
    "ㄐㄩㄢ",
    "ㄐㄩㄣ",
    "ㄐㄩㄥ",
    "ㄑㄧ",
    "ㄑㄧㄚ",
    "ㄑㄧㄝ",
    "ㄑㄧㄠ",
    "ㄑㄧㄡ",
    "ㄑㄧㄢ",
    "ㄑㄧㄣ",
    "ㄑㄧㄤ",
    "ㄑㄧㄥ",
    "ㄑㄩ",
    "ㄑㄩㄝ",
    "ㄑㄩㄢ",
    "ㄑㄩㄣ",
    "ㄑㄩㄥ",
    "ㄒㄧ",
    "ㄒㄧㄚ",
    "ㄒㄧㄝ",
    "ㄒㄧㄠ",
    "ㄒㄧㄡ",
    "ㄒㄧㄢ",
    "ㄒㄧㄣ",
    "ㄒㄧㄤ",
    "ㄒㄧㄥ",
    "ㄒㄩ",
    "ㄒㄩㄝ",
    "ㄒㄩㄢ",
    "ㄒㄩㄣ",
    "ㄒㄩㄥ",
    "ㄓ",
    "ㄓㄚ",
    "ㄓㄜ",
    "ㄓㄞ",
    "ㄓㄟ",
    "ㄓㄠ",
    "ㄓㄡ",
    "ㄓㄢ",
    "ㄓㄣ",
    "ㄓㄤ",
    "ㄓㄥ",
    "ㄓㄨ",
    "ㄓㄨㄚ",
    "ㄓㄨㄛ",
    "ㄓㄨㄞ",
    "ㄓㄨㄟ",
    "ㄓㄨㄢ",
    "ㄓㄨㄣ",
    "ㄓㄨㄤ",
    "ㄓㄨㄥ",
    "ㄔ",
    "ㄔㄚ",
    "ㄔㄜ",
    "ㄔㄞ",
    "ㄔㄠ",
    "ㄔㄡ",
    "ㄔㄢ",
    "ㄔㄣ",
    "ㄔㄤ",
    "ㄔㄥ",
    "ㄔㄨ",
    "ㄔㄨㄚ",
    "ㄔㄨㄛ",
    "ㄔㄨㄞ",
    "ㄔㄨㄟ",
    "ㄔㄨㄢ",
    "ㄔㄨㄣ",
    "ㄔㄨㄤ",
    "ㄔㄨㄥ",
    "ㄕ",
    "ㄕㄚ",
    "ㄕㄜ",
    "ㄕㄞ",
    "ㄕㄟ",
    "ㄕㄠ",
    "ㄕㄡ",
    "ㄕㄢ",
    "ㄕㄣ",
    "ㄕㄤ",
    "ㄕㄥ",
    "ㄕㄨ",
    "ㄕㄨㄚ",
    "ㄕㄨㄛ",
    "ㄕㄨㄞ",
    "ㄕㄨㄟ",
    "ㄕㄨㄢ",
    "ㄕㄨㄣ",
    "ㄕㄨㄤ",
    "ㄖ",
    "ㄖㄜ",
    "ㄖㄠ",
    "ㄖㄡ",
    "ㄖㄢ",
    "ㄖㄣ",
    "ㄖㄤ",
    "ㄖㄥ",
    "ㄖㄨ",
    "ㄖㄨㄛ",
    "ㄖㄨㄟ",
    "ㄖㄨㄢ",
    "ㄖㄨㄣ",
    "ㄖㄨㄥ",
    "ㄗ",
    "ㄗㄚ",
    "ㄗㄜ",
    "ㄗㄞ",
    "ㄗㄟ",
    "ㄗㄠ",
    "ㄗㄡ",
    "ㄗㄢ",
    "ㄗㄣ",
    "ㄗㄤ",
    "ㄗㄥ",
    "ㄗㄨ",
    "ㄗㄨㄛ",
    "ㄗㄨㄟ",
    "ㄗㄨㄢ",
    "ㄗㄨㄣ",
    "ㄗㄨㄥ",
    "ㄘ",
    "ㄘㄚ",
    "ㄘㄜ",
    "ㄘㄞ",
    "ㄘㄠ",
    "ㄘㄡ",
    "ㄘㄢ",
    "ㄘㄣ",
    "ㄘㄤ",
    "ㄘㄥ",
    "ㄘㄨ",
    "ㄘㄨㄛ",
    "ㄘㄨㄟ",
    "ㄘㄨㄢ",
    "ㄘㄨㄣ",
    "ㄘㄨㄥ",
    "ㄙ",
    "ㄙㄚ",
    "ㄙㄜ",
    "ㄙㄞ",
    "ㄙㄟ",
    "ㄙㄠ",
    "ㄙㄡ",
    "ㄙㄢ",
    "ㄙㄣ",
    "ㄙㄤ",
    "ㄙㄥ",
    "ㄙㄨ",
    "ㄙㄨㄛ",
    "ㄙㄨㄟ",
    "ㄙㄨㄢ",
    "ㄙㄨㄣ",
    "ㄙㄨㄥ",
    "ㄚ",
    "ㄛ",
    "ㄜ",
    "ㄝ",
    "ㄞ",
    "ㄟ",
    "ㄠ",
    "ㄡ",
    "ㄢ",
    "ㄣ",
    "ㄤ",
    "ㄥ",
    "ㄦ",
    "ㄧ",
    "ㄧㄚ",
    "ㄧㄛ",
    "ㄧㄝ",
    "ㄧㄞ",
    "ㄧㄠ",
    "ㄧㄡ",
    "ㄧㄢ",
    "ㄧㄣ",
    "ㄧㄤ",
    "ㄧㄥ",
    "ㄨ",
    "ㄨㄚ",
    "ㄨㄛ",
    "ㄨㄞ",
    "ㄨㄟ",
    "ㄨㄢ",
    "ㄨㄣ",
    "ㄨㄤ",
    "ㄨㄥ",
    "ㄩ",
    "ㄩㄝ",
    "ㄩㄢ",
    "ㄩㄣ",
    "ㄩㄥ",
    NULL
};

const char *PINYIN_COMBINATION_TABLES[]={
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
    "BIE",
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
    "PIE",
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
    "MIE",
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
    "DIE",
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
    "TIE",
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
    "NIE",
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
    "NÜE",
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
    "LIE",
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
    "LÜE",
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
    "JIE",
    "JIAO",
    "JIU",
    "JIAN",
    "JIN",
    "JIANG",
    "JING",
    "JU",
    "JUE",
    "JUAN",
    "JUN",
    "JIONG",
    "QI",
    "QIA",
    "QIE",
    "QIAO",
    "QIU",
    "QIAN",
    "QIN",
    "QIANG",
    "QING",
    "QU",
    "QUE",
    "QUAN",
    "QUN",
    "QIONG",
    "XI",
    "XIA",
    "XIE",
    "XIAO",
    "XIU",
    "XIAN",
    "XIN",
    "XIANG",
    "XING",
    "XU",
    "XUE",
    "XUAN",
    "XUN",
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
    "YOU",
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
    "WEN",
    "WANG",
    "WENG",
    "YU",
    "YUE",
    "YUAN",
    "YUN",
    "YONG",
    NULL
};

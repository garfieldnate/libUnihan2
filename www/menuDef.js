// Menu Definition
// Require: menu.js
// Author: Ding-Yi Chen (&#38515;&#23450;&#24413;)
// For Language setting, I use ISO 639, the code of the names of languages as identity.

var menuYOffset=23; // For Netscape 4
var menuXOffset=10; // For IE & Netscape 6
var styleString="";
var defaultLanguage="English"; // Default language
var defaultLanguageShort="En"
var languagesProvided=["English","Chinese-Simplified","Chinese-Traditional","Japanese","Korean"];
var languagesProvidedShort=["En","ZhCn","ZhTw","Jp","Kr"];
// If an object for certain encoding does not exist, then uses the object with following encoding instead.
var preferredLanguageMapping=[null,"ZhTw","En","En","En"];


/******************* English Menu Begin ******************************/
var mainMenuItemsEn=["Home","Usage", "Development","Download","Ideas Exchange"];
var usageMenuItemsEn=["Installation","Tips"];
var develMenuItemsEn=["Plan","Guide","API"];
var otherMenuItemsEn=["Forum","Bug","Project Summary"];

/******************* Chinese-Simplified Menu Begin ******************************/
var mainMenuItemsZhCn=["首页","使用说明","开发文件","下载","意见交流"];
var usageMenuItemsZhCn=["安装","使用指南"];
var develMenuItemsZhCn=["开发计画","开发指南","应用程序接口"];
var otherMenuItemsZhCn=["論壇","臭虫回报","项目摘要"];

/******************* Chinese-Traditional Menu Begin ******************************/
var mainMenuItemsZhTw=["首頁","使用說明","開發文件","下載","意見交流"];
var usageMenuItemsZhTw=["安裝","使用指南"];
var develMenuItemsZhTw=["開發計畫","開發指南","應用程式介面"];
var otherMenuItemsZhTw=["論壇","臭蟲回報","項目摘要"];

/******************* Japanese Menu Begin ******************************/
var mainMenuItemsJp=["ホームページ","利用方法", "開発文件","ダウンロードする","アイデア交換"];
var usageMenuItemsJp=["インストール","Tips"];
var develMenuItemsJp=["計画","ガイド","API"];
var otherMenuItemsJp=["フォーラム","バグ","プロジェクトの概要"];

/******************* Korean Menu Begin ******************************/
var mainMenuItemsKr=["Home","Usage", "Development","Download","Ideas Exchange"];
var usageMenuItemsKr=["Installation","Tips"];
var develMenuItemsKr=["Plan","Guide","API"];
var otherMenuItemsKr=["Forum","Bug","Project Summary"];


/******************* Multilingual Menu End ******************************/

preferredLanguage=getCookie("preferredLanguage");
if (preferredLanguage==null){
  preferredLanguage=defaultLanguage;
}
preferredLanguageShort=languageStr_get_short(preferredLanguage);

var mainMenuItems=null;
var usageMenuItems=null;
var develMenuItems=null;
var otherMenuItems=null;

var mainMenuItemArray=[
    mainMenuItemsEn, mainMenuItemsZhCn, 
    mainMenuItemsZhTw, mainMenuItemsJp,
    mainMenuItemsKr];

var usageMenuItemArray=[
    usageMenuItemsEn, usageMenuItemsZhCn, 
    usageMenuItemsZhTw, usageMenuItemsJp,
    usageMenuItemsKr];

var develMenuItemArray=[
    develMenuItemsEn, develMenuItemsZhCn,
    develMenuItemsZhTw, develMenuItemsJp,
    develMenuItemsKr];

var otherMenuItemArray=[
    otherMenuItemsEn, otherMenuItemsZhCn,
    otherMenuItemsZhTw, otherMenuItemsJp,
    otherMenuItemsKr];

var mainMenu=null;
var usageMenu=null;
var develMenu=null;
var otherMenu=null;
languageIndex=getLanguageIndex(preferredLanguage);

mainMenuItems=mainMenuItemArray[languageIndex];
usageMenuItems=usageMenuItemArray[languageIndex];
develMenuItems=develMenuItemArray[languageIndex];
otherMenuItems=otherMenuItemArray[languageIndex];

//   ["mainMenu","white","green","silver","red","horz","width='100%'",true],

mainMenu=[
   ["mainMenu","white","green","silver","red","horz","",true],
   [mainMenuItems[0],"index.html",null,null],
   [mainMenuItems[1],"usage.html","usageMenu",null],
   [mainMenuItems[2],"development.html","develMenu",null],
   [mainMenuItems[3],"http://sourceforge.net/project/showfiles.php?group_id=231871",null,null],
   [mainMenuItems[4],"","otherMenu",null]
]

usageMenu=[
   ["usageMenu","black","silver","blue","yellow","vert","",false],
   [usageMenuItems[0],"usage.html#install",null,null],
   [usageMenuItems[1],"usage.html#tips",null,null]
]

develMenu=[
   ["develMenu","black","silver","blue","yellow","vert","",false],
   [develMenuItems[0],"development.html#plan",null,null],
   [develMenuItems[1],"development.html#guide",null,null],
   [develMenuItems[2],"development.html#api",null,null]
]

otherMenu=[
   ["otherMenu","black","silver","blue","yellow","vert","",false],
   [otherMenuItems[0],"http://sourceforge.net/forum/?group_id=231871",null,null],
   [otherMenuItems[1],"http://sourceforge.net/tracker/?group_id=231871&atid=1084234",null,null],
   [otherMenuItems[2],"https://sourceforge.net/projects/libunihan/",null,null]
]

var allMenu=[mainMenu,usageMenu,develMenu,otherMenu];

var lastUpdatedEn="Last Updated:";
var lastUpdatedZhTw="&#26368;&#36817;&#26356;&#26032;&#26085;&#26399;&#65306;";
var lastUpdatedZhCn="&#26368;&#36817;&#21047;&#26032;&#26085;&#26399;&#65306;";
var lastUpdatedJp="&#26368;&#36817;&#26356;&#26032;&#26085;&#26399;&#65306;";
var lastUpdatedKo="&#47560;&#51648;&#47561; &#44060;&#51221;&#54616;&#45716; :";
var lastUpdatedTh="&#3626;&#3640;&#3604;&#3607;&#3657;&#3634;&#3618;&#3611;&#3619;&#3633;&#3610;&#3611;&#3619;&#3640;&#3591;:";

function makeAllMenus() {
//   document.write("makeAllMenus \n");
   makeMenus(allMenu);
}



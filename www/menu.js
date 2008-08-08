// Menu Functions
// The script needs global.js to work

// Origin Author: Zechs Rondall
// Reference: http://moon.tkcna.tku.edu.tw/~jack/
// Author: Ding-Yi Chen (&#38515;&#23450;&#24413;)

var menuRoot;

var menuPropertyDef=["id","menuFgColor","menuBgColor","menuOverFgColor","menuOverBgColor","direction","tableStr","alwaysVisible"]

var menuItemDef=[
   "prompt","url","submenuId","additional"
]

var menuObjArray=null;
var bodyObjArray;
var zIndex=30000

if (isIe || isDom) {
  document.body.onclick=hideAll;
  document.body.onscroll=hideAll;
  document.body.onmousemove=updateIt;
}

if (isNs4) {
  document.onmousedown=hideAll;
  document.onmousemove=updateIt;
  document.captureEvents(Event.MOUSEMOVE||Event.MOUSEDOWN);
}

function menuOver(obj,menuId,menuItemId){
   var mObj=findMenuObj(menuId);
   if (obj.style.backgroundColor){
     obj.style.backgroundColor=mObj.menuOverBgColor;
   }else if(obj.style.background){
     obj.style.background=mObj.menuOverBgColor;
   }else{
     obj.bgColor=mObj.menuOverBgColor;
   }
   obj.style.color=mObj.menuOverFgColor;
   privateMenuOver(mObj,menuItemId);
}

function nsMenuOver(obj,menuId,menuItemId){
   var mObj=findMenuObj(menuId);
   obj.bgColor=mObj.menuOverBgColor;
   privateMenuOver(mObj,menuItemId);
}

function privateMenuOver(mObj,menuItemId){
  var menuItemObj=findMenuItemObj(mObj,menuItemId);
  mObj.selected=true;
  displaySubMenu(mObj,menuItemObj);
}

function menuOut(obj,menuId,menuItemId){
  var mObj=findMenuObj(menuId);
  obj.style.backgroundColor=mObj.menuBgColor;
  obj.style.color=mObj.menuFgColor;
  privateMenuOut(mObj,menuItemId);
}

function nsMenuOut(obj,menuId,menuItemId){
  var mObj=findMenuObj(menuId);
  obj.bgColor=mObj.menuBgColor;
  privateMenuOut(mObj,menuItemId);
}

function privateMenuOut(mObj,menuItemId){
  mObj.selected=false;
  var menuItemObj=findMenuItemObj(mObj,menuItemId);
  if (!menuItemObj)
    return;
  var submenuObj=findMenuObj(menuItemObj.submenuId);
  if (submenuObj){
    submenuObj.selected=false;
//    submenuObj.showing=false;
  }
  displayMenuLayers();
}

function changeUrl(url){
  window.location=url;
}

function writeToPage(htmlBuf) {
   document.write(htmlBuf);
//   document.write("<plaintext> source code "+htmlBuf+"</plaintext>");
}

function makeMenus(menus){
   var htmlBuf="";
   var i=0;
   var mObj=null;

   htmlBuf+=styleString;
   menuObjArray=new Array(menus.length);
   for(i=0;i<menus.length;i++){
//      document.write("<BR>MenuObj["+i+"]");
      menuObjArray[i]=new MenuObj(menus[i]);
//      document.write(".id="+menuObjArray[i].id);
   }

//   document.write("<BR>menuObjArray.length="+menuObjArray.length);
   menuRoot=buildMenuTree();
   for(i=0;i<menuObjArray.length;i++){
//      document.write("<BR>menuObjArray["+i+"]");
      htmlBuf+=makeMenu(menuObjArray[i]);
   }
   writeToPage(htmlBuf);
}

function makeMenu(meObj){
   var horz=(meObj.direction=="horz")? true: false;
   var buf="";

   if (horz){
       buf+="<table width=\"100%\" bgcolor='"+meObj.menuBgColor+"' border='0' cellspacing='0' cellpadding='0'>\n";
       buf+="<tr><td>\n";
   }
   if (isOldOpera){
     buf+="<style type='text/css'>\n";
     buf+="."+meObj.id+" a:link {color:"+ meObj.menuFgColor+"; background-color:"+meObj.menuBgColor+"; text-decoraction:none}\n";
     buf+="."+meObj.id+" a:active {color:"+ meObj.menuFgColor+"; background-color:"+meObj.menuBgColor+"; text-decoraction:none}\n";
     buf+="."+meObj.id+" a:visited {color:"+ meObj.menuFgColor+"; background-color:"+meObj.menuBgColor+"; text-decoraction:none}\n";
     buf+="a."+meObj.id+":hover{color:"+ meObj.menuFgColor+"; background-color:"+meObj.menuOverBgColor+"; text-decoraction:none}\n";
     buf+="</style>\n";
   }
//   if (isNs4){
//      buf+="<layer id='"+meObj.id+"' visibility='"+toVisibilityString(meObj.alwaysVisible)+"' z-index="+"'"+zIndex+"'>\n";
//   }else{
      if (horz){
         buf+="<div id='"+meObj.id+"' style='position:relative; visibility:"+toVisibilityString(meObj.alwaysVisible)+";  z-index:"+zIndex+";'>\n ";
      }else{
         buf+="<div id='"+meObj.id+"' style='position:absolute; visibility:"+toVisibilityString(meObj.alwaysVisible)+";  z-index:"+zIndex+";'>\n ";
      }
//   }
   buf+="<table id='"+meObj.id+"_table' bgcolor='"+meObj.menuBgColor+"' border='0' cellspacing='0' cellpadding='3' "+meObj.tableStr;
   buf+=">\n";
   if (horz){
       buf+="<tr id='"+meObj.id+"_tr'>\n";
   }
   for(i=0;i<meObj.menuItems.length;i++){
      if (!horz){
	     buf+="<tr>\n";
      }
      buf+=privateAddMenuItem(meObj,meObj.menuItems[i],horz);
      if (!horz){
         buf+="</tr>\n";
      }

   }
   if (horz){
       buf+="</tr>\n";
   }
   buf+="</table>\n";
//   if (isNs4){
//      buf+="</layer>\n";
//   }else{
      buf+="</div>\n\n";
//   }
   if (horz){
       buf+="</td><td id=\"td_filler\"> <font color='"+meObj.menuBgColor+"'>space</font></td>\n";
       buf+="</tr>\n";
       buf+="</table>\n";
   }
   if (horz){
     // Adjust the Buttom line.
//      buf+="<table border='0' cellspacing='0'> <tr><td height='25' width='100%'></td></tr></table>";
   }
   return buf;
}

function MenuObj(menuDef){
   var mProperty=menuDef[0];
   var i;
   for(i=0;i<mProperty.length;i++){
//      document.write("this."+menuPropertyDef[i]+"=\""+mProperty[i]+"\"\n");
      eval("this."+menuPropertyDef[i]+"=\""+mProperty[i]+"\"");
//	eval("this."+menuPropertyDef[i]+"="+mProperty[i]);
   }
   this.parentMenuObj=null;
   this.alwaysVisible=(this.alwaysVisible=="true") ? true: false;
   this.showing=this.alwaysVisible;
   this.selected=false;
   this.menuItems=new Array(menuDef.length-1);
   for(i=1;i<menuDef.length;i++){
      this.menuItems[i-1]=menuDef[i];
      this.menuItems[i-1].id=this.id+"_i"+(i-1);
      this.menuItems[i-1].submenuObj=null;
      for(j=0;j<menuDef[i].length;j++){
//	  document.write("this.menuItems["+(i-1)+"]."+menuItemDef[j]+"='"+menuDef[i][j]+"'\n");
	 if (menuDef[i][j]!=null)
	    eval("this.menuItems['"+(i-1)+"']."+menuItemDef[j]+"='"+menuDef[i][j]+"'");
	 else
	    eval("this.menuItems['"+(i-1)+"']."+menuItemDef[j]+"=null");
      }
   }
}

// Not for directly use.
function privateAddMenuItem(meObj,menuItemObj,horz){
   var menuId=meObj.id;
   var bg=meObj.menuBgColor;
   var fg=meObj.menuFgColor;
   var menuBuf ="";
   var submenuId="";
   if (menuItemObj.submenuId!=null){
      submenuId=menuItemObj.submenuId;
   }
   if ((menuItemObj.url!=null) || (menuItemObj.submenuId!=null)){
      menuBuf += "<!-- menu item "+menuItemObj.prompt+" start -->";
      menuBuf += "<td id='"+menuItemObj.id+"_td' onMouseOver=\"menuOver(this,'"+menuId+"','"+menuItemObj.id+"')\" onMouseOut=\"menuOut(this,'"+menuId+"','"+menuItemObj.id+"')\" onClick=\"changeUrl('"+menuItemObj.url+"')\">\n";
   }else{
      menuBuf += "<td id='"+menuItemObj.id+"_td'>\n";
   }
   if (menuItemObj.url!=null || menuItemObj.submenuId!=null){
//      menuBuf += "<ilayer id='"+menuItemObj.id+"' bgcolor='"+bg+"'>\n";
//      menuBuf += "<layer OnMouseOver=\"nsMenuOver(this,'"+menuId+"','"+menuItemObj.id+"')\" OnMouseOut=\"nsMenuOut(this,'"+menuId+"','"+menuItemObj.id+"')\">\n";
   }
   menuBuf+="<nobr>";
   if (menuItemObj.url!=null){
      if (isOldOpera){
         menuBuf += "<a class='"+meObj.id+"' href='"+menuItemObj.url+"'>\n";
      }else{
       	 if (meObj.parentMenuObj!=null){
            menuBuf += "<a class='submenu' href='"+menuItemObj.url+"'>\n";
       	 }else{
            menuBuf += "<a class='menu' href='"+menuItemObj.url+"'>\n";
         }
      }
   }
   menuBuf += "<b><font color='"+fg+"'>"+menuItemObj.prompt+"</font></b>";
   if (menuItemObj.url!=null){
     menuBuf += "</a>";
   }
   if (menuItemObj.additional!=null){
      menuBuf += " "+menuItemObj.additional+" ";
   }
   menuBuf+="</nobr>";
   if (menuItemObj.url!=null || menuItemObj.submenuId!=null){
//     menuBuf += "\n</layer>";
//     menuBuf += "\n</ilayer>\n";
   }
   menuBuf+="</td>\n";
   if (horz){
      menuBuf += "<td><font color='"+fg+"'>|</font></td>\n";
   }
   menuBuf += "<!-- menu item "+menuItemObj.prompt+" end -->\n\n";
   return menuBuf;
}

function buildMenuTree(){
   var root=menuObjArray[0];
   var parentMenuObj,childMenuObj;
   for(i=0;i<menuObjArray.length;i++){
      parentMenuObj=menuObjArray[i];
      childMenuObj=null;
      for(j=0;j<parentMenuObj.menuItems.length;j++){
  	     if (parentMenuObj.menuItems[j].submenuId!=""){
	        childMenuObj=findMenuObj(parentMenuObj.menuItems[j].submenuId);
	     }
	     if (childMenuObj==null)
	        continue;
	     parentMenuObj.menuItems[j].submenuObj=childMenuObj;
	     childMenuObj.parentMenuObj=parentMenuObj;
	     if (root==childMenuObj){
	        root=parentMenuObj;
	     }
	  }
   }
   return root;
}

function findMenuObj(menuId){
   var i;
   for(i=0;i<menuObjArray.length;i++){
      if (menuObjArray[i].id==menuId){
	 return menuObjArray[i];
      }
   }
   return null;
}

function findMenuItemObj(mObj,menuItemId){
   var i;
   for(i=0;i<mObj.menuItems.length;i++){
      if (mObj.menuItems[i].id==menuItemId){
	 return mObj.menuItems[i];
      }
   }
   return null;
}

function findSubmenuObj(mObj,menuItemId){
   var i;
   for(i=0;i<mObj.menuItems.length;i++){
      if (mObj.menuItems[i].id==menuItemId){
	 return mObj.menuItems[i].submenuObj;
      }
   }
   return null;
}

/*
function hideSubmenus(mObj,menuItemId){
   var tempMObj,miObj,miId,submenuObj;
   tempMObj=mObj;
   miId=menuItemId;
   while(tempMObj!=null){
     if (miId==null){
       for(var i=0;i<tempMObj.menuItems.length;i++){
	 if (tempMObj.menuItems[i].sel){
	   miId=tempMObj.menuItems[i].id;
	   break;
	 }
       }
     }
     if (miId==null){
       break;
     }
     miObj=findMenuItemObj(tempMObj,miId);
     miObj.sel=false;
     submenuObj=findMenuObj(miObj.submenuId);
     if (submenuObj==null){
       break;
     }
     submenuObj.showing=false;
     miId=null;
     tempMObj=submenuObj;
   }
}*/

/*
function fixHorzMenu(){
   var meObj=menuObjectArray[0];
   var mainMenuTableObj=getObject(meObj.id+"_table");
   if (meObj.direction=="horz"){
//      mainMenuTableObj.width=document.offsetWidth;
      mainMenuTableObj.width=800;
   }
}
*/

function displaySubMenu(mObj,menuItemObj) {
//   var parentMenuItem,submenu;
   var submenuObj=findMenuObj(menuItemObj.submenuId);
   var subObj;
   var menuLayer,submenuLayer,menuItemLayer,tdTag;
   var i;

   for(i=0;i<mObj.menuItems.length;i++){
     subObj=findMenuObj(mObj.menuItems[i].submenuId);
     if (subObj==null){
       continue;
     }
     if (mObj.menuItems[i].id==menuItemObj.id){
       subObj.showing=true;
     }else{
       subObj.showing=false;
     }
   }

   if (submenuObj==null){
      displayMenuLayers();
      return;
   }

   if (isNs4){
     submenuLayer=document.layers[submenuObj.id];
     menuItemLayer=document.layers[mObj.id].layers[menuItemObj.id];
     submenuLayer.left=menuItemLayer.pageX;
     submenuLayer.top=menuItemLayer.pageY+menuYOffset;
   }else {
     tdTag=getObject(menuItemObj.id+"_td");
     submenuLayer=getStyleObject(submenuObj.id);
     submenuLayer.left=tdTag.offsetLeft+menuXOffset+"px";
     menuLayer=getObject(mObj.id);
     if (tdTag.offsetHeight){
       submenuLayer.top=menuLayer.offsetTop+tdTag.offsetHeight;
     }else{
       submenuLayer.top=menuLayer.offsetTop+menuYOffset;
     }
   }
   displayMenuLayers();
}

function hideAll() {
   var mObj;
   for(var i=0;i<menuObjArray.length;i++){
     mObj=menuObjArray[i];
     if (mObj.showing && (!mObj.alwaysVisible)){
	mObj.showing=false;
	mObj.selected=false;
	hideLayer(mObj.id);
     }
   }
}

function displayMenuLayers() {
  var mObj;
  if (menuObjArray==null)
      return;
  for(var i=0;i<menuObjArray.length;i++){
    mObj=menuObjArray[i];
    if (!mObj.showing && (!mObj.alwaysVisible)){
      hideLayer(mObj.id);
    }else{
      showLayer(mObj.id);
    }
  }
}

function updateIt(e) {
  displayMenuLayers();
}


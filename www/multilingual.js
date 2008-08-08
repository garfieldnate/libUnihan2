/**
 * User Language setting
 */
var languageIndex=-1; // number index that refer to user language

function getLanguageIndex(languageFullName){
    for (var i=0;i<languagesProvided.length;i++){
	if (languagesProvided[i]==languageFullName){
	    return i;
	}
    }
    return -1;
}

function languageStr_get_short(langStr){
    var i=getLanguageIndex(langStr);
    return languagesProvidedShort[i];
}

function setLanguage(){
  preferredLanguage=document.forms.languageForm.languageSelect.options[document.forms.languageForm.languageSelect.selectedIndex].text;
  if (preferredLanguage==null){
    preferredLanguage=defaultLanguage;
  }else if (preferredLanguage==""){
    preferredLanguage=defaultLanguage;
  }
  preferredLanguageShort=languageStr_get_short(preferredLanguage);

  languageIndex=getLanguageIndex(preferredLanguage);
  setCookie("preferredLanguage",preferredLanguage);
}

function reloadLanguage(){
   setLanguage();
   window.location.reload();
}

/**
 * Add the corresponding language postfix of the object
 */
function getLanguageObject(objName,languageIndex){
   var obj=null;
   if (languageIndex<0)
      return null;
   if (isDefined(objName+languagesProvidedShort[languageIndex])){
       return object_get_by_name(objName+languagesProvidedShort[languageIndex]);
   }
   for (tempIndex=findNextLanguageIndex(languageIndex);tempIndex>=0;tempIndex=findNextLanguageIndex(tempIndex)){
      if (isDefined(objName+languagesProvidedShort[tempIndex])){
	  return object_get_by_name(objName+languagesProvidedShort[tempIndex]);
      }
   }
   return null;
}


function findNextLanguageIndex(index){
   for (var i=0;i<languagesProvidedShort.length;i++){
      if (languagesProvidedShort[i]==preferredLanguageMapping[index]){
         return i;
      }
   }
   return -1;
}

/**
 * Set the div that will be shown in specified language
 *
 */
function setLangDiv(top,left,width,height,id,msg){
   document.write("<div id=\""+id+"\" style=\"position: absolute; top:"+top+"; left:"+left+"; z-index: 0; margin-top: 4pt;\">");
   document.write("<table border=\"0\" cellspacing=\"0\" height=\""+height+"\" width=\""+width+"\">");
   document.write("<tbody>");
   document.write("<tr>");
   document.write("<td>"+msg+"</td>");
   document.write("</tr>");
   document.write("</tbody>");
   document.write("</table>");
   document.write("</div>");
}


/**
 * Using empty table to keep the Space in the document
 *
 */
function keepSpace(width,height,width){
   document.write("<table border=\"0\" cellspacing=\"0\" height=\""+height+"\" width=\""+width+"\">");
   document.write("<tbody>");
   document.write("<tr>");
//   document.write("<td bgcolor=\"blue\">&#160;</td>");
   document.write("<td>&#160;</td>");
   document.write("</tr>");
   document.write("</tbody>");
   document.write("</table>");
}

function update_display(objNameArray,allObjNameArray){
    var obj=null;
    for(var i=0;i<allObjNameArray.length;i++){
	obj=getStyleObject(allObjNameArray[i]);
	obj.display="none";
    }
    for(i=0;i<objNameArray.length;i++){
	languageIndex=getLanguageIndex(preferredLanguage);
	var obj=getLanguageObject(objNameArray[i],languageIndex);
	obj.display="block";
    }
}



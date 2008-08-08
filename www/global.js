// Author: Ding-Yi Chen (&#38515;&#23450;&#24413;)

// Determin Brower Capability
var layerRef=""
var styleSwitch=""
var isDom=false;
var isNs4=false;
var isIe=false;
var isOldOpera=false;
var coun=0;
var languagesProvided;
var preferredLanguage=null;  // User preference language
var preferredLanguageShort=null;

if(document.all){
  // Internet Explorer
  layerRef="document.all"
  styleSwitch=".style"
  isIe=true;
}
if (document.layers){
  // Netscape 4
  layerRef="document.layers"
  isNs4=true;
}
if (document.getElementById){
  isDom=true;
}

for(var k in navigator){
  coun++;
}
if (coun==0){
  isOldOpera=true;
}

//if (isDom && isIe && navigator.appName.match("Opera"){
//  isOldOpera=true;
//}

Function.prototype.isFunction = true;
Function.prototype.isString = false;
String.prototype.isFunction = false;
String.prototype.isString = true;
String.prototype.isBoolean = false;
String.prototype.isNumber = false;
Number.prototype.isString = false;
Number.prototype.isFunction = false;
Number.prototype.isBoolean = false;
Number.prototype.isNumber = true;
Boolean.prototype.isString = false;
Boolean.prototype.isFunction = false;
Boolean.prototype.isBoolean = true;
Boolean.prototype.isNumber = false;
Array.prototype.itemValidation = false;
Array.prototype.isArray = true;

// from apple sample code
function getStyleObject(objectId) {
    // cross-browser function to get an object's style object given its id
    var obj=getObject(objectId);
    if (obj==null)
       return null;
    if(isDom || isIe){
       return obj.style;
    } else if (isNs4){
        // NN 4 DOM.. note: this won't find nested layers
        return document.layers[objectId];
    } else {
        return null;
    }
} // getStyleObject

function getObject(objectId){
    // cross-browser function to get an object's style object given its id
    if(isDom){
      if (document.getElementById(objectId)) {
         // W3C DOM
         return document.getElementById(objectId);
      }
    } else if (isIe && document.all(objectId)) {
        // MSIE 4 DOM
        return document.all(objectId);
    } else if (isNs4 && document.layers[objectId]) {
        // NN 4 DOM.. note: this won't find nested layers
        return document.layers[objectId];
    } else {
        return null;
    }
}

function object_get_by_name(object_name){
    try{
	var obj;
	if ((obj=getStyleObject(object_name))!=null)
	    return obj;
	if ((obj=getObject(object_name))!=null)
	    return obj;
	obj=eval(object_name);
	return obj;
    }catch(e){
//	alert(e.toString());
	return null;
    }
    return null;

}


//function getLayerLeftPostision(layerName){
//   var layerObj=getStyleObject(layerName);
//   if (isDom){
//
//   }
//   return -1;
//}

function dumpObject(obj,objName,showValue){
   var count=0;
   if (isOldOpera){
      document.write("<i>Sorry, Opera did not support <b>for(.. in ..)</b> statement. No futher information.</i>");
      return false;
   }
   for(var k in obj){
     count++;
     document.write("<b>"+objName+"."+k);
     if (showValue){
         try{
            subObj=eval("obj."+k);
            if (subObj==null){
               document.write("=</b>null \n<br />");
            }else if (subObj.isFunction){
               document.write("();</b>\n<br />");
            }else{
               document.write("=</b>"+subObj+"\n<br />");
            }
         }catch(e){
            document.write("=</b>"+e+" \n<br />");
         }
     }else{
        document.write("</b>\n<br />");
     }
   }
   document.write("<i>"+count+" attributes. </i>\n<br />");
   return true;
}

function toVisibilityString(booleanValue){
   return ((booleanValue)? "visible" : "hidden");
}

function showLayer(layerName){
//  document.write(layerRef+"['"+layerName+"']"+styleSwitch+".visibility='visible'");
   var layerObj=getStyleObject(layerName);
   if (layerObj){
      layerObj.visibility="visible";
   }
}

function hideLayer(layerName){
   var layerObj=getStyleObject(layerName);
   if (layerObj){
      layerObj.visibility="hidden";
   }
}


function dumpObjectByName(objName,showValue){
   var obj=eval(objName);
   var subObj;
   if (obj==null){
     document.write("<b>"+objName+"</b>: no such object!\n<BR>");
   }
   return showObject(obj,objName,showValue);
}

function dumpObjectById(objId,showValue){
   var obj=getObject(objId);
   var subObj;
   if (obj==null){
     document.write("<b>"+objId+"</b>: no such object!\n<BR>");
   }
   return dumpObject(obj,objId,showValue);
}

function getBrowserAttributeAsString(){
   var buf="";
   buf+="<ul>";
   buf+="   <li>Browser:";
   buf+="   <ul>";
   buf+="         <li>Name: "+navigator.appName+"</li>";
   buf+="         <li>Version: "+navigator.appVersion+"</li>";
   buf+="         <li>User agent identity: "+navigator.userAgent+"</li>";
   buf+="      </ul>";
   buf+="   </li>";
   buf+="   <li> OS: "+navigator.platform+"</li>";
   if (document.all){
     buf+="   <li>Internet Explorer 4.0 compatible.</li>";
   }
   if (document.layers){
     buf+="   <li>Netscape 4.0 compatible.</li>";
   }
   if (document.getElementById){
     buf+="   <li>DOM compatible.</li>";
   }
   if (isOldOpera){
     buf+="   <li>Opera 5 compatible.</li>";
   }
   if (navigator.cookieEnabled){
     buf+="   <li>Cookie Enable.</li>";
   }else{
     buf+="   <li>Cookie Disable.</li>";
   }

   buf+="   <li> JavaScript supported.</li>";
   buf+="</ul>";
   return buf;
}

function showBrowserAttribute(){
   documentWrite(getBrowserAttributeAsString());
}

function getScreenAttributeAsString(){
   var buf="";
   buf+="<ul>";
   buf+="   <li>Screen resolution: "+screen.width+"x"+screen.height+"</li>";
   buf+="   <li>View area (excludes taskbar): "+screen.availWidth+"x"+screen.availHeight+"</li>";
   buf+="   <li>Color depth: "+screen.colorDepth+"</li>";
   buf+="</ul>";
   return buf;
}

function isDefined(variableName){
    if (object_get_by_name(variableName)!=null)
	return true;

    return false;
}


/**
 * Source from: http://www.webreference.com/js/column8/functions.html
 *
 * name - name of the cookie
 * value - value of the cookie
 * [expires] - expiration date of the cookie (defaults to end of current session)
 * [path] - path for which the cookie is valid (defaults to path of calling document)
 * [domain] - domain for which the cookie is valid (defaults to domain of calling document)
 * [secure] - Boolean value indicating if the cookie transmission requires a secure transmission
 * an argument defaults when it is assigned null as a placeholder
 * a null placeholder is not required for trailing omitted arguments
*/
function setCookie(name, value, expires, path, domain, secure) {
  var curCookie = name + "=" + escape(value) +
      ((expires) ? "; expires=" + expires.toGMTString() : "") +
      ((path) ? "; path=" + path : "") +
      ((domain) ? "; domain=" + domain : "") +
      ((secure) ? "; secure" : "");
  document.cookie = curCookie;
}

// name - name of the desired cookie
// * return string containing value of specified cookie or null if cookie does not exist
function getCookie(name) {
  var dc = document.cookie;
  var prefix = name + "=";
  var begin = dc.indexOf("; " + prefix);
  if (begin == -1) {
    begin = dc.indexOf(prefix);
    if (begin != 0) return null;
  } else
    begin += 2;
  var end = document.cookie.indexOf(";", begin);
  if (end == -1)
    end = dc.length;
  return unescape(dc.substring(begin + prefix.length, end));
}

// name - name of the cookie
// [path] - path of the cookie (must be same as path used to create cookie)
// [domain] - domain of the cookie (must be same as domain used to create cookie)
//  path and domain default if assigned null or omitted if no explicit argument proceeds
function deleteCookie(name, path, domain) {
  if (getCookie(name)) {
    document.cookie = name + "=" +
    ((path) ? "; path=" + path : "") +
    ((domain) ? "; domain=" + domain : "") +
    "; expires=Thu, 01-Jan-70 00:00:01 GMT";
  }
}

// date - any instance of the Date object
//  hand all instances of the Date object to this function for "repairs"
function fixDate(date) {
  var base = new Date(0);
  var skew = base.getTime();
  if (skew > 0)
    date.setTime(date.getTime() - skew);
}

/**
 * Whether the string has one of the postfix
 * @return the matched postfix, null if none.
 */
function string_has_postfix(str,postfixStrArray){
    var i=0;
    var re;
    var ret;
    for(i=0;i<postfixStrArray.length;i++){
	re=new RegExp(postfixStrArray[i]+"$", "");
	ret=str.match(re);
	if (ret!=null)
	    return postfixStrArray[i];
    }
    return null;
}


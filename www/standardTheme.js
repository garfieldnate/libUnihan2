// Theme definition
// Author: Ding-Yi Chen (&#38515;&#23450;&#24413;)
// Last Modified: 2008-03-28

function themeStart(title){
  document.write("<table class=\"title\" width=\"100%\" border=\"0\" cellspacing=\"0\" cellpadding=\"3\">\n");
  document.write("<tr><th class=\"title\">"+title+"</th>\n");
  document.write("<td class=\"title\" align=\"right\" >\n");
  document.write("<form name=\"languageForm\"><select name=\"languageSelect\" onchange=\"reloadLanguage()\">");
  for(var i=0;i<languagesProvided.length;i++){
     if (languagesProvided[i]==preferredLanguage){
        document.write("<option selected=\"selected\">");
     }else{
        document.write("<option>");
     }
     document.write(languagesProvided[i]+"</option>");
  }
  document.write("</select></form></td>");
  document.write("</tr></table>\n");
  makeAllMenus();
}

/**
 * Document Footnote
 */
document.write("<p>");
document.write("<a class=\"img\" href=\"http://www.w3.org/Style/CSS/Buttons\">");
document.write("   <img alt=\"CSS\" src=\"http://www.w3.org/Style/CSS/Buttons/mwcos\" style=\"border:0;width:88px;height:31px\"/>");
document.write("</a>");

document.write("<a class=\"img\" href=\"http://validator.w3.org/check/referer\">");
document.write("   <img alt=\"Valid XHTML 1.0!\" src=\"http://www.w3.org/Icons/valid-xhtml10\" style=\"border:0;width:88px;height:31px\" />");
document.write("</a>");

document.write("<a class=\"img\" href=\"http://jigsaw.w3.org/css-validator/check/referer\">");
document.write("   <img alt=\"Valid CSS!\" src=\"http://jigsaw.w3.org/css-validator/images/vcss\" style=\"border:0;width:88px;height:31px\"/>");
document.write("</a>");

document.write("<a class=\"img\" href=\"http://sourceforge.net\">\n");
document.write("   <img src=\"http://sflogo.sourceforge.net/sflogo.php?group_id=215388&amp;type=1\"");
document.write(" width=\"88\" height=\"31\" border=\"0\" alt=\"SourceForge.net Logo\" />\n");
document.write("</a>");


//document.write("<a class=\"img\" href=\"http://my.opera.com/dychen/affiliate/\" title=\"Download Opera\">");
//document.write("   <img alt=\"Download Opera\" src=\"http://promote.opera.com/small/opera88x31.gif\" style=\"border:0;width:88px;height:31px\"/>");
//document.write("</a>");
document.write("</p>");

document.write(getLanguageObject("lastUpdated",getLanguageIndex(preferredLanguage))+"&nbsp;");
document.write(document.lastModified);
setLanguage();


#To-do list for libUnihan2

##to do on current task
* remove dependency on pwd.h

##to do tasks
* make it run on Windows, and document the process
* don't die on errors

##engineering tasks
* test suite (Check? libTAP?)
* bring code up-to-date with Unihan 6.1

##Grok tasks
* figure out the structure of the project
* learn to edit the CMake file
* get it running in CodeBlocks
* figure out the test code

##Updating to the latest Unihan distribution
It seems that the original libUnihan was designed to work with Unihan 5.1 ([version 5](http://www.unicode.org/reports/tr38/tr38-5.html)), and the current version is 6.1(version [13](http://www.unicode.org/reports/tr38/tr38-13.html)). The following are the changes that have been made. Some will require changes to this codebase, others will not.


###Revision 13

* Reissued for Unicode 6.2.0.
* Updated the regex syntax fields for kCNS1992, kIRG_GSource, and kIRG_HSource.
* Added note re CJK unified ideographs in the CJK compatibility ideographs range in Section 4.4.
* Revision 12 being a proposed update, only changes between revisions 11 and 13 are noted here.

###Revision 11

* Reissued for Unicode 6.1.
* Updated regular expressions and removed explicit start and end markers.
* Redefined the kTotalStrokes and kMandarin fields.
* Clarified the use of the kTraditionalVariant and kSimplifiedVariant fields.
* Added section 4.4 Listing of Characters Covered by the Unihan Database
* Clarified the order used for multiple values of a single field
* Revision 10 being a proposed update, only changes between revisions 9 and 11 are noted here.

###Revision 9

* Reissued for Unicode 6.0.0
* Clarified the nature of the contents of http://www.unicode.org/charts/unihan.html
* Added the History section.
* Altered the synax and source information for the IRG source fields to match current ISO/IEC 10646 values.
* Improved other regular expressions used to describe database field syntax and fixed some minor typographical errors in the field descriptions.
* The description of the kTang field was extended and that for the kHanyuPinlu field changed to reflect an extended source corpus. Other typographical errors in field descriptions were corrected.
* Clarified the nature of Japanese on and kun readings.
* Revision 8 being a proposed update, only changes between revisions 7 and 9 are noted here.

###Revision 7

* Update for Unicode 5.2.0
* Reclassified kDefinition, kHanyuPinlu, and kXHC1983 fields as Readings.
* Removed use of the Linguistic Society of Hong Kong's Jyutping Phrase Box because of viral licensing issues.
* Documented revised structure of Unihan.zip.
* Reformatted tabular listing of tags.
* Added links to tag descriptions in index tables.
* Updated regular expressions of tags.
* Revision 6 being a proposed update, only changes between revisions 5 and 7 are noted here.
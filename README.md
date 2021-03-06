Project libUnihan2

###Original project information

This project is a fork of [libUnihan](https://sourceforge.net/projects/libunihan/). The original libUnihan was created for the Unicode 5.1 version of Unihan. Several changes have been made to the database since then, and and at the time of this project, we are at Unicode 6.1.

###Original project information

Project libUnihan

This project provide a normalized SQLite Unihan database and corresponding C
library. All tables in this database are in fifth normal form.

The C API and the library is released under LGPLv2+, while the database is
released under Unicode Terms of Use (UCD, see
http://www.unicode.org/copyright.html for details).

There are three programs which provides not only database operation and query, 
but also examples that show how to use the libUnihan.

1. unihan_converter: Convert Unihan.txt to Unihan SQLite database.
2. unihan_field_validation: Verify the generated database using Unihan.txt.
3. unihan_query: Query on the database by SQL or given field value.

Normally 1 and 2 is not needed on a production system,
especially it tooks days to completed the unihan_test.

unihan_query, however, is a convenient way to access the database.

Examples:
Use as Chinese -> English dictionary.
unihan_query utf8 "<chineseCharacter>" kDefinition

Use as English -> Chinese dictionary (not perfect though).
unihan_query -L kDefinition "%<english word>%" utf8



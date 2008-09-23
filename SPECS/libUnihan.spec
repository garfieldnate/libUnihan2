Name:           libUnihan
%define         libUnihan_ver_major 0
%define         libUnihan_ver_minor 5
Version:        %{libUnihan_ver_major}.%{libUnihan_ver_minor}.1
Release:        0%{?dist}
Group:          System Environment/Libraries
License:        LGPLv2+
Summary:        C library for Unihan character database in fifth normal form 
Summary(zh_CN): 用于符合第五正规化之统汉字(Unihan)数据库的 C 库文件
Summary(zh_TW): 用於符合第五正規化之統漢字(Unihan)資料庫的 C 函式庫

BuildRoot:      %{_tmppath}/%{name}-%{version}-%{release}-root-%(%{__id_u} -n)
BuildRequires:  glib2-devel  sqlite-devel  cmake >= 2.4
#Requires:       glib2  sqlite

URL:            http://sourceforge.net/projects/libunihan
Source0:        http://downloads.sourceforge.net/libunihan/%{name}-%{version}-Source.tar.gz


%description
libUnihan provides a C library for Unihan character database in fifth
normal form (5NF).



%package devel
Summary:    Development files of libUnihan
Group:      Development/Libraries
License:        LGPLv2+
Requires:       %{name} = %{version}-%{release}
Requires:       glib2-devel  sqlite-devel

%description devel
Development files of libUnihan such as header files.

%package doc
Summary:    The libUnihan C API documents in Doxygen style
Group:      Documentation
License:        LGPLv2+
BuildRequires:  doxygen
Requires:       %{name} = %{version}-%{release}

%description doc
The libUnihan C API documents in Doxygen style.


%prep
%setup -q -n %{name}-%{version}-Source

%build
%cmake .
cmake .
make VERBOSE=1 C_DEFINES="$RPM_OPT_FLAGS" %{?_smp_mflags}
make doxygen


%install
rm -rf $RPM_BUILD_ROOT
make install DESTDIR=$RPM_BUILD_ROOT

#%check
#make test

%clean
rm -rf $RPM_BUILD_ROOT

%post -p /sbin/ldconfig

%postun  -p /sbin/ldconfig

%files
%defattr(-,root,root,-)
%doc AUTHORS NEWS README COPYING COPYING.LESSER
%{_bindir}/unihan_query
%{_libdir}/%{name}.so.%{libUnihan_ver_major}
%{_libdir}/%{name}.so.%{libUnihan_ver_major}.%{libUnihan_ver_minor}

%files devel
%defattr(-,root,root,-)
%doc ChangeLog
%{_includedir}/%{name}/
%{_libdir}/%{name}.so
%{_bindir}/unihan_converter

%files doc
%defattr(-,root,root,-)
%doc doc/html


%changelog
* Tue Sep 23 2008 Ding-Yi Chen <dchen at redhat dot com> - 0.5.1-0
- New Features:
  + PinYin accent format conversion functions (C and SQL scalar).
  + ZhuYin tone mark format conversion functions (C and SQL scalar).
  + PinYin <-->  ZhuYin conversion functions (C and SQL scalar).
  + Display as ZhuYin.
- Fixed:
  + Correct counting in FreqRank field of kMandarin table.
  + The query functions such as unihan_find_all_matched() returns SQL_Results type, to avoid the memory leaking problems.
- Changed:
  + unihanDb_open() now supports the R/W control.
  + Changed CMakefile.txt to reflects the version scheme change of UnihanDb
  + StringList type for storing const string arrays.
  + Add test suite.
  + Where-clause-generator is now able to escape the quote character(').
  + unihan_field_validation is moved to test/, therefore it will not be in binary package.
  + New make targets: rpm, srpm, rpm_db and srpm_db to generate rpm and srpm for libUnihan and UnihanDb.
- Removed:
  + unihanSql_get_result_table(). As it uses sqlite3_get_table() which might cause memory leak.

* Mon Aug 11 2008 Ding-Yi Chen <dchen at redhat dot com> - 0.4.1-1
- [Bug 453520] C#10 addressed.

* Fri Aug 08 2008 Ding-Yi Chen <dchen at redhat dot com> - 0.4.1-0
- Shows support fields and tables for unihan_query.
- Header files have moved to {include}/libUnihan.
- Completed the description of UnihanTable enumeration.
- Completed the description of str_functions.h
- In str_functions.h: unsignedStr_to_signedStr and signedStr_to_unsignedStr
clones the inputs now, while _buffer postfix for the circumstances that the buffer is given.
Addressing C#6 [Bug 453520] Review Request: libUnihan 
- rpmlint undefined-non-weak-symbol problems solved.
- Moved the include statement of private header files to Unihan_SQL_gen.c files.
- Move the doc/{name} files  to doc/{name}-{version}.
- Uhihan_enum.h and str_functions.h are now in API.

* Mon Aug 04 2008 Ding-Yi Chen <dchen at redhat dot com> - 0.4.0-0
- unihan_test now became unihan_field_vaildation
- Split the enumeration definition of Unihan.h to Unihan_enum.h
- Add unihanDb_get_tableNames() and  unihanTable_get_db_fields()
- Parameter arraySize in unihanField_array_index() is discarded.

* Fri Jul 04 2008 Ding-Yi Chen <dchen at redhat dot com> - 0.3.1-0
- Add kMandarin frequency rank support.

* Tue Jul 01 2008 Ding-Yi Chen <dchen at redhat dot com> - 0.3.0-0
- Initial public release.


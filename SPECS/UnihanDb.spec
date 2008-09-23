Name:           UnihanDb
%define         UnihanDb_name Unihan.db
%define         rel_num 7
Version:        5.1.0
Release:        %{rel_num}%{?dist}
Group:          System Environment/Libraries
License:        MIT
Summary:        The Unihan character database in fifth normal form
Summary(zh_CN): 符合第五正规化之统汉字(Unihan)数据库
Summary(zh_TW): 符合第五正規化之統漢字(Unihan)資料庫

BuildArch:      noarch
BuildRoot:      %{_tmppath}/%{name}-%{version}-root-%(%{__id_u} -n)
BuildRequires:  libUnihan-devel >= 0.5.0
Requires:	sqlite
URL:            http://www.unicode.org/charts/unihan.html

Source0:        ftp://ftp.unicode.org/Public/UNIDATA/Unihan.zip
Source1:        http://downloads.sourceforge.net/libunihan/%{name}-doc-%{version}.tar.gz

%description
UnihanDb provides a Unihan character database in fifth normal form.
The original Unihan textual data is not normalized, and further parsing 
effort is needed to obtain data from compound values of Unihan "tags".
This database splits those tag value into atom fields, thus in most case
further parsing is not required.

The version number of this package is same as the upstream Unicode
standard it follows.

%prep
%setup -q -a 1 -c -n %{name}-%{version}


%build
unihan_converter Unihan.txt %{UnihanDb_name}.%{version}-%{rel_num}

%install
rm -rf $RPM_BUILD_ROOT
mkdir -p $RPM_BUILD_ROOT/%{_datadir}/%{name}
cp %{UnihanDb_name}.%{version}-%{rel_num} $RPM_BUILD_ROOT/%{_datadir}/%{name}
ln -sf %{UnihanDb_name}.%{version}-%{rel_num} $RPM_BUILD_ROOT/%{_datadir}/%{name}/%{UnihanDb_name}

%clean
rm -rf $RPM_BUILD_ROOT

%files
%defattr(-,root,root,-)
%doc README-db ChangeLog-db
%{_datadir}/%{name}

%changelog
* Tue Sep 23 2008 Ding-Yi Chen <dchen at redhat dot com> - 5.1.0-7
- Correct counting in FreqRank field of kMandarin table.

* Thu Aug 14 2008 Ding-Yi Chen <dchen at redhat dot com> - 5.1.0-4
- Change the license to MIT.

* Mon Aug 11 2008 Ding-Yi Chen <dchen at redhat dot com> - 5.1.0-3
- Sync with upstream version.
- UnihanDb-doc version has changed from {version}-{rel} to {version}.

* Fri Aug 01 2008 Ding-Yi Chen <dchen at redhat dot com> - 5.1-2
- Field kIRGKangXi and kKangXi are split into kangXi_page, kangXi_charNum, and
kangXi_virtrul
- Field kHanyuPinlu are split into pinyin and pinyin_freq

* Fri Jul 04 2008 Ding-Yi Chen <dchen at redhat dot com> - 5.1-1
- Add kMandarin frequency rank support.


* Tue Jul 01 2008 Ding-Yi Chen <dchen at redhat dot com> - 5.1-0
- Initial public release.


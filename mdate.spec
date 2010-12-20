%define name mdate
%define version 1.5.8
%define release 1
%define prefix /usr
%define docdir %{_datadir}/doc/%{name}
%define htmldir %{docdir}/html
%define license GPL

Summary: mdate, a utility to report and convert Mayan calendar dates
Name: %{name}
Version: %{version}
Release: %{release}
License: %{license}
Group: Applications/System
Source: Mdate-%{version}.tar.gz
URL: http://mdate.sourceforge.net
Packager: Sean Dwyer <ewe2@users.sourceforge.net>
Buildroot: %{_tmppath}/%{name}-%{version}-root
AutoReq: 0
Requires: libc6 >= 2.3.2, libgcc1 >= 3.3.1, libstdc++5 >= 3.3.1
Epoch: 1

%description
Mdate is a command-line tool similar to date(1) to convert between Mayan and
Gregorian calendar dates, with optional language defaults and date-like
formatted output.

%prep

%setup -q

%build
make
make createdoc

%install
rm -rf $RPM_BUILD_ROOT
mkdir -p $RPM_BUILD_ROOT
mkdir -p $RPM_BUILD_ROOT%{_bindir}
mkdir -p $RPM_BUILD_ROOT%{_mandir}/man1
mkdir -p $RPM_BUILD_ROOT%{htmldir}

make DESTDIR=$RPM_BUILD_ROOT installdoc
make DESTDIR=$RPM_BUILD_ROOT install

%clean
rm -rf $RPM_BUILD_ROOT

%files
%defattr(-, root, root)
%{docdir}/README
%{docdir}/ChangeLog
%{docdir}/AUTHORS
%{docdir}/Translators
%{docdir}/API
%{docdir}/GPL
%{docdir}/NEWS
%{docdir}/mdate.sgml*
%{docdir}/mdate.text*
%{docdir}/mdate.dvi*
%{docdir}/mdate.ps*
%{_bindir}/mdate
%{_mandir}/man1/mdate.1*
%{htmldir}/mdate-*.html
%{htmldir}/mdate.html

%changelog
* Fri 29 May 2009 Sean Dwyer <ewe2@users.sourceforge.net>
- found the server, no major changes, new release.
* Sun Dec 19 2004 Sean Dwyer <ewe2@users.sourceforge.net>
- interim release until we find the right subversion server.
* Mon Jun 14 2004 Sean Dwyer <ewe2@users.sourceforge.net>
- new release.
* Sun May 30 2004 Sean Dwyer <ewe2@users.sourceforge.net>
- new version
* Thu May 27 2004 Sean Dwyer <ewe2@users.sourceforge.net>
- updated version, changed email
* Fri Oct 10 2003 Sean Dwyer <ewe2@users.sourceforge.net>
- hacked together a basic spec file.

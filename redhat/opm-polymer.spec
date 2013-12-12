#
# spec file for package opm-polymer
#

%define tag rc3

Name:           opm-polymer
Version:        2013.10
Release:        0
Summary:        Open Porous Media - polymer library
License:        GPL-3.0
Group:          Development/Libraries/C and C++
Url:            http://www.opm-project.org/
Source0:        https://github.com/OPM/%{name}/archive/release/%{version}/%{tag}.tar.gz#/%{name}-%{version}.tar.gz
BuildRequires:  blas-devel lapack-devel dune-common-devel
BuildRequires:  git suitesparse-devel cmake28 doxygen bc ert.ecl-devel
BuildRequires:  tinyxml-devel dune-istl-devel superlu-devel opm-core-devel
%{?el5:BuildRequires: gcc44 gcc44-gfortran gcc44-c++}
%{!?el5:BuildRequires: gcc gcc-gfortran gcc-c++}
%{?el5:BuildRequires: boost141-devel}
%{!?el5:BuildRequires: boost-devel}
BuildRoot:      %{_tmppath}/%{name}-%{version}-build
Requires:       libopm-polymer1 = %{version}

%description
This module is the polymer part of OPM.

%package -n libopm-polymer1
Summary:        Open Porous Media - polymer library
Group:          System/Libraries
%{?el5:BuildArch: %{_arch}}

%description -n libopm-polymer1
This module is the polymer part of OPM.

%package bin
Summary:        Open Porous Media - polymer library - applications
Group:          Science
%{?el5:BuildArch: %{_arch}}

%description bin
This module is the polymer part of OPM.

%package devel
Summary:        Development and header files for opm-polymer
Group:          Development/Libraries/C and C++
Requires:       blas-devel
Requires:       lapack-devel
Requires:       suitesparse-devel
Requires:       libopm-polymer1 = %{version}
%{?el5:BuildArch: %{_arch}}

%description devel
This module is the polymer part of OPM.

%package doc
Summary:        Documentation files for opm-polymer
Group:          Documentation
BuildArch:	noarch

%description doc
This package contains the documentation files for opm-polymer

%{?el5:
%package debuginfo
Summary:        Debug info in opm-polymer
Group:          Scientific
Requires:       libopm-polymer1 = %{version}, opm-polymer-bin = %{version}
BuildArch: 	%{_arch}

%description debuginfo
This package contains the debug symbols for opm-polymer
}

%prep
%setup -q -n %{name}-release-%{version}-%{tag}

# consider using -DUSE_VERSIONED_DIR=ON if backporting
%build
cmake28 -DBUILD_SHARED_LIBS=1 -DCMAKE_BUILD_TYPE=Release -DCMAKE_INSTALL_PREFIX=%{_prefix} -DCMAKE_INSTALL_DOCDIR=share/doc/%{name}-%{version} -DUSE_RUNPATH=OFF %{?el5:-DCMAKE_CXX_COMPILER=g++44 -DCMAKE_C_COMPILER=gcc44 -DBOOST_LIBRARYDIR=%{_libdir}/boost141 -DBOOST_INCLUDEDIR=/usr/include/boost141}
make

%install
make install DESTDIR=${RPM_BUILD_ROOT}
make install-html DESTDIR=${RPM_BUILD_ROOT}

%clean
rm -rf %{buildroot}

%post -n libopm-polymer1 -p /sbin/ldconfig

%postun -n libopm-polymer1 -p /sbin/ldconfig

%files doc
%{_docdir}/*

%files -n libopm-polymer1
%defattr(-,root,root,-)
%{_libdir}/*.so.*

%files devel
%defattr(-,root,root,-)
%{_libdir}/*.so
%{_libdir}/dunecontrol/*
%{_libdir}/pkgconfig/*
%{_includedir}/*
%{_datadir}/cmake/*

%files bin
%{_bindir}/*

%{?el5:
%files debuginfo
/usr/lib/debug/%{_libdir}/*.so.*.debug
}

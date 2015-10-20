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
BuildRequires:  blas-devel lapack-devel dune-common-devel boost148-devel
BuildRequires:  git suitesparse-devel doxygen bc ert.ecl-devel opm-common-devel
BuildRequires:  tinyxml-devel dune-istl-devel eigen3-devel
BuildRequires:  opm-core-devel opm-parser-devel opm-autodiff-devel opm-material-devel
%{?el6:BuildRequires: cmake28 devtoolset-2 superlu-devel }
%{!?el6:BuildRequires: cmake gcc gcc-gfortran gcc-c++ SuperLU-devel}
BuildRoot:      %{_tmppath}/%{name}-%{version}-build
Requires:       libopm-polymer1 = %{version}

%description
This module is the polymer part of OPM.

%package -n libopm-polymer1
Summary:        Open Porous Media - polymer library
Group:          System/Libraries

%description -n libopm-polymer1
This module is the polymer part of OPM.

%package bin
Summary:        Open Porous Media - polymer library - applications
Group:          Science

%description bin
This module is the polymer part of OPM.

%package devel
Summary:        Development and header files for opm-polymer
Group:          Development/Libraries/C and C++
Requires:       blas-devel
Requires:       lapack-devel
Requires:       suitesparse-devel
Requires:       libopm-polymer1 = %{version}

%description devel
This module is the polymer part of OPM.

%package doc
Summary:        Documentation files for opm-polymer
Group:          Documentation
BuildArch:	noarch

%description doc
This package contains the documentation files for opm-polymer

%prep
%setup -q -n %{name}-release-%{version}-%{tag}

# consider using -DUSE_VERSIONED_DIR=ON if backporting
%build
%{?el6:scl enable devtoolset-2 bash}
%{?el6:cmake28} %{!?el6:cmake} -DBUILD_SHARED_LIBS=1 -DCMAKE_BUILD_TYPE=Release -DCMAKE_INSTALL_PREFIX=%{_prefix} -DCMAKE_INSTALL_DOCDIR=share/doc/%{name}-%{version} -DUSE_RUNPATH=OFF %{?el6:-DCMAKE_CXX_COMPILER=/opt/rh/devtoolset-2/root/usr/bin/g++ -DCMAKE_C_COMPILER=/opt/rh/devtoolset-2/root/usr/bin/gcc} -DBOOST_LIBRARYDIR=%{_libdir}/boost148 -DBOOST_INCLUDEDIR=/usr/include/boost148
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

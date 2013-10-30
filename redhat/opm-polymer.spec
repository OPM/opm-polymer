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
BuildRequires:  blas-devel gcc-c++ gcc-gfortran lapack-devel dune-common-devel
BuildRequires:  boost-devel git suitesparse-devel cmake28 doxygen bc
BuildRequires:  tinyxml-devel dune-istl-devel superlu-devel opm-core-devel
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
Requires:       %{name} = %{version}
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
cmake28 -DBUILD_SHARED_LIBS=1 -DCMAKE_BUILD_TYPE=Release -DCMAKE_INSTALL_PREFIX=%{_prefix} -DCMAKE_INSTALL_DOCDIR=share/doc/%{name}-%{version} -DWHOLE_PROG_OPTIM=ON -DUSE_RUNPATH=OFF
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

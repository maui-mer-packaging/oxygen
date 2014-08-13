# 
# Do NOT Edit the Auto-generated Part!
# Generated by: spectacle version 0.27
# 

Name:       oxygen

# >> macros
# << macros

Summary:    KDE's default style and look
Version:    5.0.0
Release:    1
Group:      System/Base
License:    GPLv2+
URL:        http://www.kde.org
Source0:    %{name}-%{version}.tar.xz
Source100:  oxygen.yaml
Source101:  oxygen-rpmlintrc
Requires:   kf5-filesystem
Requires(post): /sbin/ldconfig
Requires(postun): /sbin/ldconfig
BuildRequires:  pkgconfig(Qt5Core)
BuildRequires:  pkgconfig(Qt5DBus)
BuildRequires:  pkgconfig(Qt5Xml)
BuildRequires:  pkgconfig(Qt5Network)
BuildRequires:  pkgconfig(Qt5Gui)
BuildRequires:  pkgconfig(Qt5Widgets)
BuildRequires:  pkgconfig(Qt5Concurrent)
BuildRequires:  pkgconfig(Qt5Test)
BuildRequires:  pkgconfig(Qt5WebKit)
BuildRequires:  pkgconfig(Qt5Qml)
BuildRequires:  pkgconfig(Qt5Quick)
BuildRequires:  pkgconfig(Qt5Script)
BuildRequires:  pkgconfig(Qt5X11Extras)
BuildRequires:  pkgconfig(xcb)
BuildRequires:  kf5-rpm-macros
BuildRequires:  extra-cmake-modules
BuildRequires:  ki18n-devel
BuildRequires:  kconfig-devel
BuildRequires:  kconfigwidgets-devel
BuildRequires:  kguiaddons-devel
BuildRequires:  kwidgetsaddons-devel
BuildRequires:  kservice-devel
BuildRequires:  kcompletion-devel
BuildRequires:  frameworkintegration-devel
BuildRequires:  kwindowsystem-devel
BuildRequires:  kwin-devel

%description
KDE's default style and look.


%package devel
Summary:    Development files for %{name}
Group:      Development/Libraries
Requires:   %{name} = %{version}-%{release}

%description devel
The %{name}-devel package contains the files necessary to develop applications
that use %{name}.


%package cursor-themes
Summary:    Oxygen cursor themes
Group:      System/Base
BuildArch:  noarch

%description cursor-themes
A full set of cursor themes.


%package sounds
Summary:    Oxygen sounds
Group:      System/Base
BuildArch:  noarch

%description sounds
A full set of sounds for different desktop events.


%package kwin
Summary:    KWin "Oxygen" decoration
Group:      System/Base
Requires:   %{name} = %{version}-%{release}
Requires:   kwin

%description kwin
This package contains the "Oxygen" decoration for KWin.


%package style
Summary:    QtWidgets "Oxygen" style
Group:      System/Base
Requires:   %{name} = %{version}-%{release}

%description style
This package contains the "Oxygen" style for QtWidgets.


%prep
%setup -q -n %{name}-%{version}/upstream

# >> setup
# << setup

%build
# >> build pre
%kf5_make
# << build pre



# >> build post
# << build post

%install
rm -rf %{buildroot}
# >> install pre
%kf5_make_install
# << install pre

# >> install post
# << install post

%files
%defattr(-,root,root,-)
%doc COPYING
%{_kf5_bindir}/oxygen-demo5
%{_kf5_bindir}/oxygen-settings5
%{_kf5_libdir}/*.so.*
# >> files
# << files

%files devel
%defattr(-,root,root,-)
%{_kf5_libdir}/*.so
# >> files devel
# << files devel

%files cursor-themes
%defattr(-,root,root,-)
%{_kf5_sharedir}/icons/*
# >> files cursor-themes
# << files cursor-themes

%files sounds
%defattr(-,root,root,-)
%{_kf5_sharedir}/sounds/*
# >> files sounds
# << files sounds

%files kwin
%defattr(-,root,root,-)
%{_kf5_plugindir}/kwin/kdecorations/config/kwin_oxygen_config.so
%{_kf5_plugindir}/kwin/kdecorations/kwin3_oxygen.so
# >> files kwin
# << files kwin

%files style
%defattr(-,root,root,-)
%{_kf5_plugindir}/kstyle_oxygen_config.so
%{_kf5_plugindir}/styles/oxygen.so
%{_kf5_sharedir}/kstyle/themes/oxygen.themerc
# >> files style
# << files style

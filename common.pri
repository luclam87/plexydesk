CONFIG(release, debug|release) {
    build_postfix = release
}

CONFIG(debug, debug|release) {
    build_postfix = debug
}

top_builddir     = $${OUT_PWD}/$${top_srcdir}/build/plexydesk-ready-build
top_destdirbin   = $${top_builddir}/bin
top_destdirlib   = $${top_builddir}/lib
top_outdir       = $${OUT_PWD}/$${top_srcdir}/build

builddir         = $${top_outdir}/$${build_postfix}/$${srcdir}
plexyext         = $${top_destdirlib}/plexyext
sharedir         = $${top_builddir}/share
qtimports        = $${top_builddir}/qt4/imports

OBJECTS_DIR      = $$builddir/.objs
MOC_DIR          = $$builddir/.mocs
UI_DIR           = $$builddir/.uis
RCC_DIR          = $$builddir/.rccs
DESTDIR          = $${top_destdirlib}

LIBS += -L$${top_destdirlib} -L$${top_destdirbin}

DEPENDPATH += . $${top_srcdir} $${top_destdirlib}

INCLUDEPATH += . .. $${top_srcdir}/build $${top_outdir}

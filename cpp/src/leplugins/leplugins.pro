TEMPLATE = subdirs

SUBDIRS += \
    plugina_test \
    pluginb_test

plugina_test.depends = lepluginframework
pluginb_test.depends = lepluginframework

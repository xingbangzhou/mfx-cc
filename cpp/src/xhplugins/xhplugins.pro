TEMPLATE = subdirs

SUBDIRS += \
    plugina_test \
    pluginb_test

plugina_test.depends = xhpluginframework
pluginb_test.depends = xhpluginframework

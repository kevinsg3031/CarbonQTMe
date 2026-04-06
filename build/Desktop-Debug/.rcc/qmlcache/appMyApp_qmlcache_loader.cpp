#include <QtQml/qqmlprivate.h>
#include <QtCore/qdir.h>
#include <QtCore/qurl.h>
#include <QtCore/qhash.h>
#include <QtCore/qstring.h>

namespace QmlCacheGeneratedCode {
namespace _qt_qml_MyApp_Main_qml { 
    extern const unsigned char qmlData[];
    extern const QQmlPrivate::AOTCompiledFunction aotBuiltFunctions[];
    const QQmlPrivate::CachedQmlUnit unit = {
        reinterpret_cast<const QV4::CompiledData::Unit*>(&qmlData), &aotBuiltFunctions[0], nullptr
    };
}
namespace _qt_qml_MyApp_pages_Dashboard_qml { 
    extern const unsigned char qmlData[];
    extern const QQmlPrivate::AOTCompiledFunction aotBuiltFunctions[];
    const QQmlPrivate::CachedQmlUnit unit = {
        reinterpret_cast<const QV4::CompiledData::Unit*>(&qmlData), &aotBuiltFunctions[0], nullptr
    };
}
namespace _qt_qml_MyApp_pages_Processes_qml { 
    extern const unsigned char qmlData[];
    extern const QQmlPrivate::AOTCompiledFunction aotBuiltFunctions[];
    const QQmlPrivate::CachedQmlUnit unit = {
        reinterpret_cast<const QV4::CompiledData::Unit*>(&qmlData), &aotBuiltFunctions[0], nullptr
    };
}
namespace _qt_qml_MyApp_pages_EnergyEstimator_qml { 
    extern const unsigned char qmlData[];
    extern const QQmlPrivate::AOTCompiledFunction aotBuiltFunctions[];
    const QQmlPrivate::CachedQmlUnit unit = {
        reinterpret_cast<const QV4::CompiledData::Unit*>(&qmlData), &aotBuiltFunctions[0], nullptr
    };
}
namespace _qt_qml_MyApp_components_SidebarButton_qml { 
    extern const unsigned char qmlData[];
    extern const QQmlPrivate::AOTCompiledFunction aotBuiltFunctions[];
    const QQmlPrivate::CachedQmlUnit unit = {
        reinterpret_cast<const QV4::CompiledData::Unit*>(&qmlData), &aotBuiltFunctions[0], nullptr
    };
}
namespace _qt_qml_MyApp_components_StatCard_qml { 
    extern const unsigned char qmlData[];
    extern const QQmlPrivate::AOTCompiledFunction aotBuiltFunctions[];
    const QQmlPrivate::CachedQmlUnit unit = {
        reinterpret_cast<const QV4::CompiledData::Unit*>(&qmlData), &aotBuiltFunctions[0], nullptr
    };
}
namespace _qt_qml_MyApp_components_DoughnutStat_qml { 
    extern const unsigned char qmlData[];
    extern const QQmlPrivate::AOTCompiledFunction aotBuiltFunctions[];
    const QQmlPrivate::CachedQmlUnit unit = {
        reinterpret_cast<const QV4::CompiledData::Unit*>(&qmlData), &aotBuiltFunctions[0], nullptr
    };
}
namespace _qt_qml_MyApp_components_PidThreadsChart_qml { 
    extern const unsigned char qmlData[];
    extern const QQmlPrivate::AOTCompiledFunction aotBuiltFunctions[];
    const QQmlPrivate::CachedQmlUnit unit = {
        reinterpret_cast<const QV4::CompiledData::Unit*>(&qmlData), &aotBuiltFunctions[0], nullptr
    };
}
namespace _qt_qml_MyApp_components_TableHeader_qml { 
    extern const unsigned char qmlData[];
    extern const QQmlPrivate::AOTCompiledFunction aotBuiltFunctions[];
    const QQmlPrivate::CachedQmlUnit unit = {
        reinterpret_cast<const QV4::CompiledData::Unit*>(&qmlData), &aotBuiltFunctions[0], nullptr
    };
}
namespace _qt_qml_MyApp_components_RingChart_qml { 
    extern const unsigned char qmlData[];
    extern const QQmlPrivate::AOTCompiledFunction aotBuiltFunctions[];
    const QQmlPrivate::CachedQmlUnit unit = {
        reinterpret_cast<const QV4::CompiledData::Unit*>(&qmlData), &aotBuiltFunctions[0], nullptr
    };
}
namespace _qt_qml_MyApp_components_Theme_qml { 
    extern const unsigned char qmlData[];
    extern const QQmlPrivate::AOTCompiledFunction aotBuiltFunctions[];
    const QQmlPrivate::CachedQmlUnit unit = {
        reinterpret_cast<const QV4::CompiledData::Unit*>(&qmlData), &aotBuiltFunctions[0], nullptr
    };
}

}
namespace {
struct Registry {
    Registry();
    ~Registry();
    QHash<QString, const QQmlPrivate::CachedQmlUnit*> resourcePathToCachedUnit;
    static const QQmlPrivate::CachedQmlUnit *lookupCachedUnit(const QUrl &url);
};

Q_GLOBAL_STATIC(Registry, unitRegistry)


Registry::Registry() {
    resourcePathToCachedUnit.insert(QStringLiteral("/qt/qml/MyApp/Main.qml"), &QmlCacheGeneratedCode::_qt_qml_MyApp_Main_qml::unit);
    resourcePathToCachedUnit.insert(QStringLiteral("/qt/qml/MyApp/pages/Dashboard.qml"), &QmlCacheGeneratedCode::_qt_qml_MyApp_pages_Dashboard_qml::unit);
    resourcePathToCachedUnit.insert(QStringLiteral("/qt/qml/MyApp/pages/Processes.qml"), &QmlCacheGeneratedCode::_qt_qml_MyApp_pages_Processes_qml::unit);
    resourcePathToCachedUnit.insert(QStringLiteral("/qt/qml/MyApp/pages/EnergyEstimator.qml"), &QmlCacheGeneratedCode::_qt_qml_MyApp_pages_EnergyEstimator_qml::unit);
    resourcePathToCachedUnit.insert(QStringLiteral("/qt/qml/MyApp/components/SidebarButton.qml"), &QmlCacheGeneratedCode::_qt_qml_MyApp_components_SidebarButton_qml::unit);
    resourcePathToCachedUnit.insert(QStringLiteral("/qt/qml/MyApp/components/StatCard.qml"), &QmlCacheGeneratedCode::_qt_qml_MyApp_components_StatCard_qml::unit);
    resourcePathToCachedUnit.insert(QStringLiteral("/qt/qml/MyApp/components/DoughnutStat.qml"), &QmlCacheGeneratedCode::_qt_qml_MyApp_components_DoughnutStat_qml::unit);
    resourcePathToCachedUnit.insert(QStringLiteral("/qt/qml/MyApp/components/PidThreadsChart.qml"), &QmlCacheGeneratedCode::_qt_qml_MyApp_components_PidThreadsChart_qml::unit);
    resourcePathToCachedUnit.insert(QStringLiteral("/qt/qml/MyApp/components/TableHeader.qml"), &QmlCacheGeneratedCode::_qt_qml_MyApp_components_TableHeader_qml::unit);
    resourcePathToCachedUnit.insert(QStringLiteral("/qt/qml/MyApp/components/RingChart.qml"), &QmlCacheGeneratedCode::_qt_qml_MyApp_components_RingChart_qml::unit);
    resourcePathToCachedUnit.insert(QStringLiteral("/qt/qml/MyApp/components/Theme.qml"), &QmlCacheGeneratedCode::_qt_qml_MyApp_components_Theme_qml::unit);
    QQmlPrivate::RegisterQmlUnitCacheHook registration;
    registration.structVersion = 0;
    registration.lookupCachedQmlUnit = &lookupCachedUnit;
    QQmlPrivate::qmlregister(QQmlPrivate::QmlUnitCacheHookRegistration, &registration);
}

Registry::~Registry() {
    QQmlPrivate::qmlunregister(QQmlPrivate::QmlUnitCacheHookRegistration, quintptr(&lookupCachedUnit));
}

const QQmlPrivate::CachedQmlUnit *Registry::lookupCachedUnit(const QUrl &url) {
    if (url.scheme() != QLatin1String("qrc"))
        return nullptr;
    QString resourcePath = QDir::cleanPath(url.path());
    if (resourcePath.isEmpty())
        return nullptr;
    if (!resourcePath.startsWith(QLatin1Char('/')))
        resourcePath.prepend(QLatin1Char('/'));
    return unitRegistry()->resourcePathToCachedUnit.value(resourcePath, nullptr);
}
}
int QT_MANGLE_NAMESPACE(qInitResources_qmlcache_appMyApp)() {
    ::unitRegistry();
    return 1;
}
Q_CONSTRUCTOR_FUNCTION(QT_MANGLE_NAMESPACE(qInitResources_qmlcache_appMyApp))
int QT_MANGLE_NAMESPACE(qCleanupResources_qmlcache_appMyApp)() {
    return 1;
}

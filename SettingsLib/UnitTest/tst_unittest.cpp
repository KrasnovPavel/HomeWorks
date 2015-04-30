#include <QString>
#include <QtTest>
#include <settings.h>

class UnitTest : public QObject
{
    Q_OBJECT

public:
    UnitTest();

private Q_SLOTS:
    //tests for base version
    void checkBaseWriting();
    void checkBaseReset();

    //tests for bonus functions
    void checkBonusWriting();
    void checkBonusReset();
    void checkCastInt();
    void checkCastDouble();
    void checkCastBoolean();
    void checkOperatorsInt();
    void checkOperatorsDouble();
    void checkOperatorsBoolean();
    void checkOperatorsString();
};

UnitTest::UnitTest()
{
}

void UnitTest::checkBaseWriting()
{
    settings *test = new settings("test.ini");
    test->set("first", "value1~@345434EDS");
    test->set("sA-_987^", "892IU842U4B&%$(");
    test->set("second", "true");
    test->set("third", "23");

    QCOMPARE(test->get("first", "default"), std::string("value1~@345434EDS"));
    QCOMPARE(test->get("sA-_987^", "default"), std::string("892IU842U4B&%$("));
    QCOMPARE(test->get("second", "default"), std::string("true"));
    QCOMPARE(test->get("third", "default"), std::string("23"));
    QCOMPARE(test->get("forth", "default"), std::string("default"));

    test->reload();

    QCOMPARE(test->get("first", "default"), std::string("value1~@345434EDS"));
    QCOMPARE(test->get("sA-_987^", "default"), std::string("892IU842U4B&%$("));
    QCOMPARE(test->get("second", "default"), std::string("true"));
    QCOMPARE(test->get("third", "default"), std::string("23"));
    QCOMPARE(test->get("forth", "default"), std::string("default"));

    delete test;

    test = new settings("test.ini");

    QCOMPARE(test->get("first", "default"), std::string("value1~@345434EDS"));
    QCOMPARE(test->get("sA-_987^", "default"), std::string("892IU842U4B&%$("));
    QCOMPARE(test->get("second", "default"), std::string("true"));
    QCOMPARE(test->get("third", "default"), std::string("23"));
    QCOMPARE(test->get("forth", "default"), std::string("default"));

    test->reset();
    delete test;
}

void UnitTest::checkBaseReset()
{
    settings *test = new settings("test.ini");
    test->set("first", "value1~@345434EDS");
    test->set("sA-_987^", "892IU842U4B&%$(");
    test->set("second", "true");
    test->set("third", "23");

    QCOMPARE(test->get("first", "default"), std::string("value1~@345434EDS"));
    QCOMPARE(test->get("sA-_987^", "default"), std::string("892IU842U4B&%$("));
    QCOMPARE(test->get("second", "default"), std::string("true"));
    QCOMPARE(test->get("third", "default"), std::string("23"));
    QCOMPARE(test->get("forth", "default"), std::string("default"));

    test->reset();

    QCOMPARE(test->get("first", "default"), std::string("default"));
    QCOMPARE(test->get("sA-_987^", "default"), std::string("default"));
    QCOMPARE(test->get("second", "default"), std::string("default"));
    QCOMPARE(test->get("third", "default"), std::string("default"));
    QCOMPARE(test->get("forth", "default"), std::string("default"));

    test->reload();

    QCOMPARE(test->get("first", "default"), std::string("default"));
    QCOMPARE(test->get("sA-_987^", "default"), std::string("default"));
    QCOMPARE(test->get("second", "default"), std::string("default"));
    QCOMPARE(test->get("third", "default"), std::string("default"));
    QCOMPARE(test->get("forth", "default"), std::string("default"));

    delete test;

    test = new settings("test.ini");

    QCOMPARE(test->get("first", "default"), std::string("default"));
    QCOMPARE(test->get("sA-_987^", "default"), std::string("default"));
    QCOMPARE(test->get("second", "default"), std::string("default"));
    QCOMPARE(test->get("third", "default"), std::string("default"));
    QCOMPARE(test->get("forth", "default"), std::string("default"));

    test->reset();
    delete test;
}

void UnitTest::checkBonusWriting()
{
    settings* test = new settings("test.ini");
    (*test)["first"] = "value1~@345434EDS";
    (*test)["sA-_987^"] = "892IU842U4B&%$(";
    (*test)["second"] = "true";
    (*test)["third"] = "23";
    (*test)["double"] = "764.3";

    QCOMPARE((std::string)(*test)["first"], std::string("value1~@345434EDS"));
    QCOMPARE((std::string)(*test)["sA-_987^"], std::string("892IU842U4B&%$("));
    QCOMPARE((std::string)(*test)["second"], std::string("true"));
    QCOMPARE((std::string)(*test)["third"], std::string("23"));
    QCOMPARE((std::string)(*test)["double"], std::string("764.3"));
    QVERIFY_EXCEPTION_THROWN(int y = (*test)["forth"], EmptyProperty);

    test->reload();

    QCOMPARE((std::string)(*test)["first"], std::string("value1~@345434EDS"));
    QCOMPARE((std::string)(*test)["sA-_987^"], std::string("892IU842U4B&%$("));
    QCOMPARE((std::string)(*test)["second"], std::string("true"));
    QCOMPARE((std::string)(*test)["third"], std::string("23"));
    QCOMPARE((std::string)(*test)["double"], std::string("764.3"));
    QVERIFY_EXCEPTION_THROWN(int y = (*test)["forth"], EmptyProperty);

    delete test;

    test = new settings("test.ini");

    QCOMPARE((std::string)(*test)["first"], std::string("value1~@345434EDS"));
    QCOMPARE((std::string)(*test)["sA-_987^"], std::string("892IU842U4B&%$("));
    QCOMPARE((std::string)(*test)["second"], std::string("true"));
    QCOMPARE((std::string)(*test)["third"], std::string("23"));
    QCOMPARE((std::string)(*test)["double"], std::string("764.3"));
    QVERIFY_EXCEPTION_THROWN(int y = (*test)["forth"], EmptyProperty);


    test->reset();
    delete test;
}

void UnitTest::checkBonusReset()
{
    settings* test = new settings("test.ini");
    (*test)["first"] = "value1~@345434EDS";
    (*test)["sA-_987^"] ="892IU842U4B&%$(";
    (*test)["second"] = "true";
    (*test)["third"] = "23";
    (*test)["double"] = "764.3";

    QCOMPARE((std::string)(*test)["first"], std::string("value1~@345434EDS"));
    QCOMPARE((std::string)(*test)["sA-_987^"], std::string("892IU842U4B&%$("));
    QCOMPARE((std::string)(*test)["second"], std::string("true"));
    QCOMPARE((std::string)(*test)["third"], std::string("23"));
    QCOMPARE((std::string)(*test)["double"], std::string("764.3"));
    QVERIFY_EXCEPTION_THROWN(int y = (*test)["forth"], EmptyProperty);

    test->reset();

    QVERIFY_EXCEPTION_THROWN(int y = (*test)["first"], EmptyProperty);
    QVERIFY_EXCEPTION_THROWN(int y = (*test)["sA-_987"], EmptyProperty);
    QVERIFY_EXCEPTION_THROWN(int y = (*test)["second"], EmptyProperty);
    QVERIFY_EXCEPTION_THROWN(int y = (*test)["third"], EmptyProperty);
    QVERIFY_EXCEPTION_THROWN(int y = (*test)["double"], EmptyProperty);
    QVERIFY_EXCEPTION_THROWN(int y = (*test)["forth"], EmptyProperty);

    test->reload();

    QVERIFY_EXCEPTION_THROWN(int y = (*test)["first"], EmptyProperty);
    QVERIFY_EXCEPTION_THROWN(int y = (*test)["sA-_987"], EmptyProperty);
    QVERIFY_EXCEPTION_THROWN(int y = (*test)["second"], EmptyProperty);
    QVERIFY_EXCEPTION_THROWN(int y = (*test)["third"], EmptyProperty);
    QVERIFY_EXCEPTION_THROWN(int y = (*test)["double"], EmptyProperty);
    QVERIFY_EXCEPTION_THROWN(int y = (*test)["forth"], EmptyProperty);

    test->reset();
    delete test;
}

void UnitTest::checkCastInt()
{
    settings* test = new settings("test.ini");
    (*test)["first"] = "value1~@345434EDS";
    (*test)["sA-_987^"] ="892IU842U4B&%$(";
    (*test)["second"] = "true";
    (*test)["third"] = "23";
    (*test)["double"] = "764.3";


    QCOMPARE((std::string)(*test)["first"], std::string("value1~@345434EDS"));
    QCOMPARE((std::string)(*test)["sA-_987^"], std::string("892IU842U4B&%$("));
    QCOMPARE((std::string)(*test)["second"], std::string("true"));
    QCOMPARE((std::string)(*test)["third"], std::string("23"));
    QCOMPARE((std::string)(*test)["double"], std::string("764.3"));


    QVERIFY_EXCEPTION_THROWN(int y = (*test)["forth"], EmptyProperty);

    QVERIFY_EXCEPTION_THROWN(int y = (*test)["first"], std::invalid_argument);
    QVERIFY_EXCEPTION_THROWN(int y = (*test)["sA-_987^"], std::invalid_argument);
    QVERIFY_EXCEPTION_THROWN(int y = (*test)["second"], std::invalid_argument);
    QCOMPARE((int)(*test)["third"], 23);
    QCOMPARE((int)(*test)["double"], (int)764.3);


    test->reset();
    delete test;
}

void UnitTest::checkCastDouble()
{
    settings* test = new settings("test.ini");
    (*test)["first"] = "value1~@345434EDS";
    (*test)["sA-_987^"] ="892IU842U4B&%$(";
    (*test)["second"] = "true";
    (*test)["third"] = "23";
    (*test)["double"] = "764.3";


    QCOMPARE((std::string)(*test)["first"], std::string("value1~@345434EDS"));
    QCOMPARE((std::string)(*test)["sA-_987^"], std::string("892IU842U4B&%$("));
    QCOMPARE((std::string)(*test)["second"], std::string("true"));
    QCOMPARE((std::string)(*test)["third"], std::string("23"));
    QCOMPARE((std::string)(*test)["double"], std::string("764.3"));

    QVERIFY_EXCEPTION_THROWN(int y = (*test)["forth"], EmptyProperty);

    QVERIFY_EXCEPTION_THROWN(int y = (*test)["first"], std::invalid_argument);
    QVERIFY_EXCEPTION_THROWN(int y = (*test)["sA-_987^"], std::invalid_argument);
    QVERIFY_EXCEPTION_THROWN(int y = (*test)["second"], std::invalid_argument);
    QCOMPARE((double)(*test)["third"], (double)23);
    QCOMPARE((double)(*test)["double"], 764.3);

    test->reset();
    delete test;
}

void UnitTest::checkCastBoolean()
{
    settings* test = new settings("test.ini");
    (*test)["first"] = "value1~@345434EDS";
    (*test)["sA-_987^"] ="892IU842U4B&%$(";
    (*test)["second"] = "true";
    (*test)["third"] = "23";
    (*test)["double"] = "764.3";


    QCOMPARE((std::string)(*test)["first"], std::string("value1~@345434EDS"));
    QCOMPARE((std::string)(*test)["sA-_987^"], std::string("892IU842U4B&%$("));
    QCOMPARE((std::string)(*test)["second"], std::string("true"));
    QCOMPARE((std::string)(*test)["third"], std::string("23"));
    QCOMPARE((std::string)(*test)["double"], std::string("764.3"));

    QVERIFY_EXCEPTION_THROWN(bool y = (*test)["forth"], EmptyProperty);

    QVERIFY_EXCEPTION_THROWN(bool y = (*test)["first"], std::invalid_argument);
    QVERIFY_EXCEPTION_THROWN(bool y = (*test)["sA-_987^"], std::invalid_argument);
    QCOMPARE((bool)(*test)["second"], true);
    QVERIFY_EXCEPTION_THROWN(bool y = (*test)["third"], std::invalid_argument);
    QVERIFY_EXCEPTION_THROWN(bool y = (*test)["double"], std::invalid_argument);

    test->reset();
    delete test;
}

void UnitTest::checkOperatorsInt()
{
    settings* test = new settings("test.ini");
    (*test)["first"] = "value1~@345434EDS";
    (*test)["sA-_987^"] ="892IU842U4B&%$(";
    (*test)["second"] = "true";
    (*test)["third"] = "23";
    (*test)["double"] = "764.3";


    QCOMPARE((std::string)(*test)["first"], std::string("value1~@345434EDS"));
    QCOMPARE((std::string)(*test)["sA-_987^"], std::string("892IU842U4B&%$("));
    QCOMPARE((std::string)(*test)["second"], std::string("true"));
    QCOMPARE((std::string)(*test)["third"], std::string("23"));
    QCOMPARE((std::string)(*test)["double"], std::string("764.3"));
    QVERIFY_EXCEPTION_THROWN(int y = (*test)["forth"], EmptyProperty);


    QVERIFY_EXCEPTION_THROWN((*test)["first"] += 5, std::invalid_argument);
    QVERIFY_EXCEPTION_THROWN((*test)["first"] /= 5, std::invalid_argument);
    QVERIFY_EXCEPTION_THROWN((*test)["first"] *= 5, std::invalid_argument);
    QVERIFY_EXCEPTION_THROWN((*test)["first"] -= 5, std::invalid_argument);

    QVERIFY_EXCEPTION_THROWN((*test)["second"] += 5, std::invalid_argument);
    QVERIFY_EXCEPTION_THROWN((*test)["second"] /= 5, std::invalid_argument);
    QVERIFY_EXCEPTION_THROWN((*test)["second"] *= 5, std::invalid_argument);
    QVERIFY_EXCEPTION_THROWN((*test)["second"] -= 5, std::invalid_argument);

    QVERIFY_EXCEPTION_THROWN((*test)["sA-_987^"] += 5, std::invalid_argument);
    QVERIFY_EXCEPTION_THROWN((*test)["sA-_987^"] /= 5, std::invalid_argument);
    QVERIFY_EXCEPTION_THROWN((*test)["sA-_987^"] *= 5, std::invalid_argument);
    QVERIFY_EXCEPTION_THROWN((*test)["sA-_987^"] -= 5, std::invalid_argument);

    QCOMPARE(int((*test)["third"] += 5), 23+5);
    QCOMPARE(int((*test)["third"] -= 5), 23);
    QCOMPARE(int((*test)["third"] *= 5), 23*5);
    QCOMPARE(int((*test)["third"] /= 5), 23);

    QCOMPARE(int((*test)["double"] += 5), (int)764+5);
    QCOMPARE(int((*test)["double"] -= 5), (int)764);
    QCOMPARE(int((*test)["double"] *= 5), (int)764*5);
    QCOMPARE(int((*test)["double"] /= 5), (int)764);

    QVERIFY_EXCEPTION_THROWN((*test)["forth"] += 2, EmptyProperty);
    QVERIFY_EXCEPTION_THROWN((*test)["forth"] /= 2, EmptyProperty);
    QVERIFY_EXCEPTION_THROWN((*test)["forth"] *= 2, EmptyProperty);
    QVERIFY_EXCEPTION_THROWN((*test)["forth"] -= 2, EmptyProperty);

    test->reset();
    delete test;
}

void UnitTest::checkOperatorsDouble()
{
    settings* test = new settings("test.ini");
    (*test)["first"] = "value1~@345434EDS";
    (*test)["sA-_987^"] ="892IU842U4B&%$(";
    (*test)["second"] = "true";
    (*test)["third"] = "23";
    (*test)["double"] = "764.3";


    QCOMPARE((std::string)(*test)["first"], std::string("value1~@345434EDS"));
    QCOMPARE((std::string)(*test)["sA-_987^"], std::string("892IU842U4B&%$("));
    QCOMPARE((std::string)(*test)["second"], std::string("true"));
    QCOMPARE((std::string)(*test)["third"], std::string("23"));
    QCOMPARE((std::string)(*test)["double"], std::string("764.3"));
    QVERIFY_EXCEPTION_THROWN(int y = (*test)["forth"], EmptyProperty);


    QVERIFY_EXCEPTION_THROWN((*test)["first"] += 5.5, std::invalid_argument);
    QVERIFY_EXCEPTION_THROWN((*test)["first"] /= 5.5, std::invalid_argument);
    QVERIFY_EXCEPTION_THROWN((*test)["first"] *= 5.5, std::invalid_argument);
    QVERIFY_EXCEPTION_THROWN((*test)["first"] -= 5.5, std::invalid_argument);

    QVERIFY_EXCEPTION_THROWN((*test)["second"] += 5.5, std::invalid_argument);
    QVERIFY_EXCEPTION_THROWN((*test)["second"] /= 5.5, std::invalid_argument);
    QVERIFY_EXCEPTION_THROWN((*test)["second"] *= 5.5, std::invalid_argument);
    QVERIFY_EXCEPTION_THROWN((*test)["second"] -= 5.5, std::invalid_argument);

    QVERIFY_EXCEPTION_THROWN((*test)["sA-_987^"] += 5.5, std::invalid_argument);
    QVERIFY_EXCEPTION_THROWN((*test)["sA-_987^"] /= 5.5, std::invalid_argument);
    QVERIFY_EXCEPTION_THROWN((*test)["sA-_987^"] *= 5.5, std::invalid_argument);
    QVERIFY_EXCEPTION_THROWN((*test)["sA-_987^"] -= 5.5, std::invalid_argument);

    QCOMPARE(double((*test)["third"] += 5.5), 23+5.5);
    QCOMPARE(double((*test)["third"] -= 5.5), (double)23);
    QCOMPARE(double((*test)["third"] *= 5.5), 23*5.5);
    QCOMPARE(double((*test)["third"] /= 5.5), (double)23);

    QCOMPARE(double((*test)["double"] += 5.5), 764.3+5.5);
    QCOMPARE(double((*test)["double"] -= 5.5), 764.3);
    QCOMPARE(double((*test)["double"] *= 5.5), 764.3*5.5);
    QCOMPARE(double((*test)["double"] /= 5.5), 764.3);

    QVERIFY_EXCEPTION_THROWN((*test)["forth"] += 2.2, EmptyProperty);
    QVERIFY_EXCEPTION_THROWN((*test)["forth"] /= 2.2, EmptyProperty);
    QVERIFY_EXCEPTION_THROWN((*test)["forth"] *= 2.2, EmptyProperty);
    QVERIFY_EXCEPTION_THROWN((*test)["forth"] -= 2.2, EmptyProperty);

    test->reset();
    delete test;
}

void UnitTest::checkOperatorsBoolean()
{
    settings* test = new settings("test.ini");
    (*test)["first"] = "value1~@345434EDS";
    (*test)["sA-_987^"] ="892IU842U4B&%$(";
    (*test)["second"] = "true";
    (*test)["third"] = "23";
    (*test)["double"] = "764.3";


    QCOMPARE((std::string)(*test)["first"], std::string("value1~@345434EDS"));
    QCOMPARE((std::string)(*test)["sA-_987^"], std::string("892IU842U4B&%$("));
    QCOMPARE((std::string)(*test)["second"], std::string("true"));
    QCOMPARE((std::string)(*test)["third"], std::string("23"));
    QCOMPARE((std::string)(*test)["double"], std::string("764.3"));
    QVERIFY_EXCEPTION_THROWN(int y = (*test)["forth"];, EmptyProperty);


    QVERIFY_EXCEPTION_THROWN((*test)["first"] |= true, std::invalid_argument);
    QVERIFY_EXCEPTION_THROWN((*test)["first"] &= false, std::invalid_argument);

    QVERIFY_EXCEPTION_THROWN((*test)["sA-_987^"] |= true, std::invalid_argument);
    QVERIFY_EXCEPTION_THROWN((*test)["sA-_987^"] &= false, std::invalid_argument);

    QVERIFY_EXCEPTION_THROWN((*test)["third"] |= true, std::invalid_argument);
    QVERIFY_EXCEPTION_THROWN((*test)["third"] &= false, std::invalid_argument);

    QVERIFY_EXCEPTION_THROWN((*test)["double"] |= true, std::invalid_argument);
    QVERIFY_EXCEPTION_THROWN((*test)["double"] &= false, std::invalid_argument);

    QCOMPARE(bool((*test)["second"] &= false), false);
    QCOMPARE(bool((*test)["second"] |= true), true);


    QVERIFY_EXCEPTION_THROWN((*test)["forth"] |= true, EmptyProperty);
    QVERIFY_EXCEPTION_THROWN((*test)["forth"] &= false, EmptyProperty);

    test->reset();
    delete test;
}

void UnitTest::checkOperatorsString()
{
    settings* test = new settings("test.ini");
    (*test)["first"] = "value1~@345434EDS";


    QCOMPARE((std::string)(*test)["first"], std::string("value1~@345434EDS"));
    QVERIFY_EXCEPTION_THROWN(std::string y = (*test)["forth"], EmptyProperty);

    QCOMPARE(std::string((*test)["first"] += "gdyhsvkjhfvsghdvs129361874#$%$@"),
             std::string("value1~@345434EDSgdyhsvkjhfvsghdvs129361874#$%$@"));


    QVERIFY_EXCEPTION_THROWN((*test)["forth"] += "true", EmptyProperty);

    test->reset();
    delete test;

}



QTEST_APPLESS_MAIN(UnitTest)

#include "tst_unittest.moc"

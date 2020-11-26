#include "mainwindow.h"
#include <iostream>
#include <assert.h>
#include "dictionary_hash.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    //Тест конструктора по умолчанию
    dictionary_hash<string> collection;
    assert(collection.size() == 0);


    //Добавление ключа
    collection << "Hello";
    assert(collection.size() == 1);

    //Добавление существующего ключа
    collection << "Hello";
    assert(collection.size() == 1);
    assert(collection["Hello"] == 2);

    //Проверка наличия ключа
    assert(collection.in_dictionary("Hello") == 1);

    //Проверка []
    assert(collection["Hello"] == 2);

    //Проверка удаления
    //Не существует ключ
    collection.delete_word("World");
    assert(collection.size() == 1);
    //Существует ключ
    collection.delete_word("Hello");
    assert(collection.size() == 0);

    //Проверка наличия удаленного ключа
    assert(collection.in_dictionary("Hello") == 0);

    //Коллекция после удаления и новая
    dictionary_hash<string> collection2;
    assert(collection == collection2);

    //Конструктор копирования
    dictionary_hash<string> collection_copy(collection);
    assert(collection == collection_copy);
    //Равенство после вставки
    collection_copy << "Hello";
    assert(collection != collection_copy);

    //Проверка загрузки из файла и записи в файл
    dictionary_hash<string> collection_out;
    collection_out << "Hello";
    collection_out << "World";
    assert(collection_out.output_to_file("test_out.txt") == 1);
    dictionary_hash<string> collection_in;
    assert(collection_in.input_from_file("test_out.txt") == 1);
    assert(collection_in == collection_out);

    //Проверка удаления всего списка
    assert(collection_in.clear() == 1);
    assert(collection_in.size() == 0);

    //Проверка метода принимающего число
    assert(collection_out.count(1) == 2);

    cout << "All tests are passed";

    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}

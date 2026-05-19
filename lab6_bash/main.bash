#!/bin/bash

# проверка аргументов
if [ $# -ne 1 ]; then
    echo "Использование: $0 <файл>"
    echo "Пример: $0 notes.txt"
    exit 1
fi

TARGET=$1

# проверка что файл существует
if [ ! -f "$TARGET" ]; then
    echo "Ошибка: файл '$TARGET' не найден"
    exit 1
fi

# получаем суффикс файла
SUFFIX="${TARGET##*.}"

# проверка что суффикс есть
if [ "$SUFFIX" = "$TARGET" ]; then
    echo "Ошибка: у файла нет суффикса"
    exit 1
fi

echo "Целевой файл: $TARGET"
echo "Ищем файлы с суффиксом .${SUFFIX} ..."
echo ""

COUNT=0

# перебираем все файлы с таким же суффиксом
while IFS= read -r FILE; do
    # пропускаем сам целевой файл
    if [ "$FILE" = "$TARGET" ]; then
        continue
    fi

    # сравниваем файлы побайтово через cmp
    if cmp -s "$TARGET" "$FILE"; then
        echo "Совпадает: $FILE — удаляем"
        rm "$FILE"
        COUNT=$((COUNT + 1))
    else
        echo "Отличается: $FILE"
    fi

done < <(find . -name "*.${SUFFIX}" -type f)

echo ""
echo "Готово. Удалено файлов: ${COUNT}"

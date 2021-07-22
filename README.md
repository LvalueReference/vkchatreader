# vk-cli
Программа для вывода сообщений из чата вк вам в консоль, которая полностью написана на **C++**
# Подготовка
1. Создать группу вк и скопировать из неё данные для работы с **VK API**
    - Перейти по [**этой**](https://vk.com/groups?w=groups_create) ссылке и создать группу вк
    - Далее зайти в *управление* группой и во вкладке **настройки** под полем для ввода адреса будет текст "*Номер сообщества — clubXXXXXXXXX.*"
      Нас интересуют 9 цифр после "club" и до точки. Скопируйте эти цифры
        
    - Перейти во вкладку **Работа с API** и создать новый *ключ доступа* со всеми правами. Скопируйте этот ключ
        
    - Перейти по [**этой**](https://vkhost.github.io/) ссылке и создать ключ доступа к *User API*.
      Выбрать можно любой из перечисленных вариантов, но я рекомендую использовать **VK Me**.
      Далее следовать инструкции из самого сайта для получения токена. Сохраните эти данные
2. Добавить бота в группу
   - В настройках бота перейти во вкладку `Сообщения -> Настройки для бота`, тыкнуть на галочку рядом с полем 
   **"Разрешать добавлять сообщество в беседы"** и сохранить изменения
   - Добавить бота в вашу беседу с помощью кнопки, которая появилась на главной странице вашей группы  
3. Клонирование репозитория
   - В нужной вам директории клонируйте репозиторий с помощью команды
     ```commandline
     git clone https://github.com/LvalueReference/vk-cli.git
     ```
   - Перейти в директорию с помощью команды
     ```commandline
     cd vk-cli
     ```
4. Настройка конфиг-файла
  - Перейти по директории `config/` и редактировать файл `config.json`
  - Заполните конфиг данными, которые вы копировали из *пункта 1*
  - В поле `API_V` нужно указать последнюю версию **VK Api**, узнать её можно [**здесь**](https://vk.com/dev/versions)

# Сборка
1. Установка библиотек (**cmake**, **libcurl**, **libcurlpp**, **libfmt**)
   - С помощью пакетного менеджера вашего дистрибутива установить библиотеки. Рассмотрим 2 примера:
       1. Debian-based дистрибутивы: 
          ```commandline
          sudo apt update
          sudo apt install cmake libcurl4 libcurl4-openssl-dev libcurlpp-dev libfmt-dev --yes
          ```
       2. Arch-based дистрибутивы:
          ```commandline
          sudo pacman -Syu
          sudo pacman -Sy cmake libcurl4 libcurl4-openssl-dev libcurlpp-dev libfmt-dev 
          ```
2. Сборка и запуск программы
     ```commandline
     mkdir cmake-files
     cd cmake-files
     cmake ../
     make
     ./vkreader
     ```

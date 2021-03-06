# Требования к проекту «Mind games»

# Содержание
1 [Введение](#intro)  
2 [Требования пользователя](#user_requirements)  
2.1 [Программные интерфейсы](#software_interfaces)  
2.2 [Интерфейс пользователя](#user_interface)  
2.3 [Характеристики пользователей](#user_specifications)   
2.4 [Предположения и зависимости](#assumptions_and_dependencies)  
3 [Системные требования](#system_requirements)  
3.1 [Функциональные требования](#functional_requirements)  
3.2 [Нефункциональные требования](#non-functional_requirements)  
3.2.1 [Атрибуты качества](#quality_attributes)  
 
<a name="intro"/>

# 1 Введение

Целью проекта под названием «Mind games» является помощь в проведении интеллектуальных игр. Автоматической фиксации нарушений - фальстартов, очередность отвечающих, а так же отсчёт отведенного на ответ времени, подсчёт баллов и выявление победителя.

<a name="user_requirements"/>

# 2 Требования пользователя

<a name="software_interfaces"/>

## 2.1 Программные интерфейсы

Для работы устройства требуется наличие на этапе компиляции необходимых библиотек.
В частности:
- EEPROM.h
- Wire.h
- LiquidCrystal_I2C.h

<a name="user_interface"/>

## 2.2 Интерфейс пользователя

Проект разрабатывается, как мобильное устройство, предусматривающее управление с помощью кнопок.
Взаимодействие с пользователем осуществляется при помощи отображения информации на экране.
Для каждой команды предусмотрены кнопки, нажимая на которые команда сообщает о своём желании отвечать на вопрос.

**Основное меню:**
![Основное меню](https://github.com/AndreiP88/Mind-games/blob/master/Documents/Requirements/images/main.png)

**Режим игры:**
![Игра Брейн-ринг](https://github.com/AndreiP88/Mind-games/blob/master/Documents/Requirements/images/b_r.png)

<a name="user_specifications"/>

## 2.3 Характеристики пользователей

Проект рассчитан на людей всех возрастов вне зависимости от пола. Для пользованием устройством не требуются специальные навыки.

<a name="assumptions_and_dependencies"/>

## 2.4 Предположения и зависимости

Устройство разрабатывается с ориентиром на людей, любящих интеллектуальные игры. Для полноценной работы устройства требуется один ведущий и четыре команды.

<a name="system_requirements"/>

# 3 Системные требования

Устройство работает на контроллере ATMega328.
Требуется внешний источник питания или питание от батареек.

<a name="functional_requirements"/>

## 3.1 Функциональные требования

Устройство должно регистрировать нажатия кнопок команд.

Устройство должно отображать для ведущего номер команды первой нажавшей на кнопку (в соответствии с выбранной игрой).

Устройство должно запоминать очередность нажатий  (в соответствии с выбранной игрой).

Устройство должно подавать звуковой сигнал о начале раунда.

Устройство должно сигнализировать об истечении времени отведённого на раунд за 5 секунд до конца.

Устройство должно подсчитывать баллы для каждой команды.

<a name="non-functional_requirements"/>

## 3.2 Нефункциональные требования

Отображаемая информация должна быть интуитивно понятной.

Взаимодействие с устройство при помощи кнопок навигации должно быть очевидным.

<a name="quality_attributes"/>

## 3.2.1 АТРИБУТЫ КАЧЕСТВА

Стабильная работа устройства, так как от стабильности работы устройства зависити итоговый результат игры.
Быстрый отклик (<10мс) на кнопок командами.
Легкость и простота в использовании.

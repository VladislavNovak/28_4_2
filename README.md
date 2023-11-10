<details open>
<summary><span style="color:tomato;font-size:16px">THREADS</span></summary>
<details open>
<summary><span style="color:tomato;font-size:12px">Симуляция работы вокзала</span></summary>

С помощью многопоточности реализуйте простую модель железнодорожного вокзала.

С трёх точек отправления в разное время отбывают три разных поезда с условными обозначениями A, B, C. 
Все они идут на один и тот же вокзал и могут дойти до него в разное время.

На этом целевом вокзале единовременно может находиться только один поезд. 
Остальные поезда должны ждать, пока уже занятое место освободится.

В начале программы пользователь последовательно вводит для каждого поезда время в пути до вокзала (в секундах). 
После этого поезда начинают своё движение за заданное количество времени. 
Как только поезд прибыл на вокзал, он ожидает от пользователя команды depart, 
которая сигнализирует о его отбытии с вокзала.

По всем событиям (прибытие на вокзал, ожидание свободного места, отбытие с вокзала) 
вместе с условным обозначением поезда выводятся сообщения в консоль.

Программа завершается, когда на вокзале побывают все три поезда.

Совет: используйте для вокзала отдельный мьютекс и симулируйте ожидание с помощью него.

</details>

<details open>
<summary><span style="color:tomato;font-size:12px">INFO</span></summary>

<a href="https://radioprog.ru/post/1403" style="margin-left:16px">Многопоточность в C++. Управление потоками</a>

<a href="https://nuancesprog.ru/p/5452/" style="margin-left:16px">многопоточность, конкурентность и параллелизм</a>

<a href="https://raymii.org/s/articles/Cpp_async_threads_and_user_input.html" style="margin-left:16px">C++ async, threads and user input</a>

<a href="https://stackoverflow.com/questions/32350909/taking-input-over-standard-i-o-in-multithreaded-application" style="margin-left:16px">Taking input over standard I/O in multithreaded application</a>

</details>
</details>
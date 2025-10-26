how to compile the program?

cd home/asus/learncpp/library_oop/build/Desktop-Debug
rm -rf *			#remove -r(thư mục con) -f(force không hỏi xác nhận)
qmake ../../library_oop.pro	#qmake đọc file .pro để sinh ra Makefile. với 
				file .pro nằm ở cấp 2 thư mục
				Makefile cho make biết cách biên dịch toàn bộ ctrinh
make -j4			#make đọc Makefile do qmake sinh ra và biên dịch
				toàn bộ mã nguồn, 
				-j4 chạy song song 4 tiếng trình phù hợp với CPU 4 
				core.
				make -j4 sinh ra file executable là library_oop

How to run the program?
./library_oop

output:
Starting library application...
Library initialized
Worker created
Worker moved to thread
Connected searchCompleted signal
Connected sortedListReady signal
Connected reportGenerated signal
Connected progressUpdate signal
Connected taskFinished signal
Connected thread finished signal
Sample data added
Printing header: QUẢN LÝ THƯ VIỆN SÁCH - OOP + THREAD + ALGO
Printed header
Printed menu prompt
=== QUẢN LÝ THƯ VIỆN SÁCH - OOP + THREAD + ALGO ===
Lệnh: add, list, search <kw>, borrow <isbn>, return <isbn>, report, sort, quit
> 
#input:
>add 978-1-234-56789-0 "C++ Primer" "Lippman" 2012
>list
>search C++
>borrow 978-0-13-110362-7
>report
>sort
>quit


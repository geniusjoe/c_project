from cyaron import *  # 引入CYaRon的库

io = IO("testdata.in", disable_output=True)
max_page = 1000
book_length = 500000
ques_length = 2
ques_max = 2e9
io.input_writeln(1, book_length, ques_length)
for i in range(book_length):
    io.input_write(randint(1, max_page))
io.input_writeln()
# initial page
for i in range(ques_length):
    set_data = [1, 0, 1, 0]
    set_data[1] = randint(1, book_length)
    set_data[3] = randint(set_data[1], book_length)
    set_data.append(randint(1, ques_max))
    io.input_writeln(set_data)

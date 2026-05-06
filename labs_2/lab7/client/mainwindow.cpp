#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <iostream>
#include "../shared/inc.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_connect_button_clicked()
{
    asio::io_context io_context;
try {

            asio::ip::tcp::endpoint endpoint(asio::ip::make_address(ui->ip_line->text().toStdString()), ui->port_line->text().toShort());

            // Создаём сокет
            asio::ip::tcp::socket socket(io_context);

            try {
                std::cout << "Connecting to server" << std::endl;

                // Подключаемся
                socket.connect(endpoint);

                std::cout << "Connected!" << std::endl;
            }
            catch (const std::exception& ex) {
                std::cout << "Server is unavailable" << std::endl;
            }

            // Отправляем сообщение
            std::string message = "Hello from client!";
            asio::write(socket, asio::buffer(message));

            std::cout << "Sended: " << message << std::endl;

            // Получаем ответ
            char reply[2];
            std::error_code ec;
            size_t length = socket.read_some(asio::buffer(reply), ec);

            if (!ec) {
                std::cout << "Server reply: " << std::endl;

                short info = reinterpret_cast<short>(reply);
                std::cerr << info << std::endl;
            } else {
                std::cout << "Ошибка получения ответа: " << ec.message() << std::endl;
            }


} catch (const std::exception& e) {
    std::cerr << "Ошибка: " << e.what() << std::endl;
} catch (...) {
    std::cerr << "Unhandled exception!" << std::endl;
}
}


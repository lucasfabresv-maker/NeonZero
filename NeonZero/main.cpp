#include "C:\Users\lucas\Downloads\crow_all.h" // Biblioteca do servidor
#include <nlohmann/json.hpp>
#include <iostream>

using json = nlohmann::json;

int main() {
    crow::SimpleApp app;

    // Rota para o Celular acessar: http://seu-ip:8080/
    CROW_ROUTE(app, "/")([]() {
        return "<h1>Neon Zero Online</h1><p>Conectado ao PC.</p>";
        });

    // Rota do WebSocket (Onde o ESP vai fluir em tempo real)
    CROW_ROUTE(app, "/ws")
        .websocket()
        .onopen([&](crow::websocket::connection& conn) {
        std::cout << "[+] Celular conectado!" << std::endl;
            })
        .onmessage([&](crow::websocket::connection& conn, const std::string& data, bool is_binary) {
        // Se você clicar no botão 'Panic' no celular, o comando chega aqui
        if (data == "PANIC") {
            std::cout << "[!] PANIC KEY ATIVADA PELO CELULAR!" << std::endl;
            exit(0);
        }
            });

    std::cout << "[*] Neon Server rodando na porta 8080..." << std::endl;
    app.port(8080).multithreaded().run();
}
int preparations(){
    std::cout << "Prod. by XAHZX6R" << std::endl;
    std::cout << "FSD is prepared..." << std::endl;

    // Задержка перед началом отсчета
    std::this_thread::sleep_for(std::chrono::seconds(1));

    int count = 3;
    for (int i = 0; i < 3; ++i) {
        std::cout << "\rStart in " << count-- << "    ";
        std::cout.flush();
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }

    std::cout << std::endl << "FSD enabled!" << std::endl;

    return 0;
}
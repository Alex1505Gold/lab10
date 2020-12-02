#include <iostream>
#include <string>
#include <filesystem>

namespace fs = std::filesystem;

int main(int argc, char* argv[])
{
    std::string comand;
    std::string new_dir, file_name, copy_to, del_dir;
    std::string go_to_dir_name, dir_name, new_file_name, new_dir_name;
    fs::path cur_path, copy_to_path, new_path;
    std::getline(std::cin, comand);
    while (comand != "end")
    {
        //1
        if (comand == "show_cur_path")
        {
            std::cout << fs::current_path() << std::endl;
        }
        //2
        if (comand == "what_in_cur_dir")
        {
            for (auto& p : fs::directory_iterator(fs::current_path()))
            {
                cur_path = p.path();
                //std::cout << p.path() << "  ---  ";
                std::cout << cur_path.filename() << std::endl;
            }
        }
        //3
        if (comand == "create_dir")
        {
            std::getline(std::cin, new_dir);
            cur_path = fs::current_path();
            cur_path /= new_dir;
            //std::cout << cur_path << std::endl;
            if (!(fs::exists(cur_path))) fs::create_directory(new_dir);
        }
        //4
        if (comand == "file_size")
        {
            std::getline(std::cin, file_name);
            cur_path = fs::current_path() / file_name;
            if (fs::exists(cur_path)) std::cout << fs::file_size(cur_path) << std::endl;
        }
        //5
        if (comand == "copy_file")
        {
            //сначала ввод файла, который копируем, потом ввод названия нового файла
            std::getline(std::cin, file_name);
            cur_path = fs::current_path() / file_name;
            copy_to_path = fs::current_path();
            std::getline(std::cin, copy_to);
            copy_to_path /= copy_to;
            fs::copy_file(cur_path, copy_to_path);
        }
        //6
        if (comand == "delete_file")
        {
            std::getline(std::cin, file_name);
            cur_path = fs::current_path() / file_name;
            fs::remove(cur_path);
        }
        //7
        if (comand == "delete_dir")
        {
            std::getline(std::cin, del_dir);
            cur_path = fs::current_path() / del_dir;
            fs::remove_all(cur_path);
        }
        //8
        if (comand == "go_forward")
        {
            std::getline(std::cin, go_to_dir_name); 
            cur_path = fs::current_path() / go_to_dir_name;
            fs::create_directory(go_to_dir_name);
            fs::current_path(cur_path);
            std::cout << fs::current_path() << std::endl;
            //std::cout << fs::current_path().remove_filename() << std::endl;
        }
        if (comand == "go_back")
        {
            cur_path = fs::current_path().remove_filename();
            fs::current_path(cur_path);
            std::cout << fs::current_path() << std::endl;
        }
        //9
        //сначала ввод старого имени, потом нового
        if (comand == "rename_file")
        {
            std::getline(std::cin, file_name);
            
            std::getline(std::cin, new_file_name);
            
            //переименование для файла
            cur_path = fs::current_path() / file_name;
            new_path = fs::current_path() / new_file_name;
            fs::rename(cur_path, new_path);
            //fs::rename(new_path, cur_path);//вернул как было, чтобы каждый раз назад не менять
        }
        //переименование для папки
        if (comand == "rename_dir")
        {
            std::getline(std::cin, dir_name);
            std::getline(std::cin, new_dir_name);
            cur_path = fs::current_path() / dir_name;
            new_path = fs::current_path() / new_dir_name;
            fs::rename(cur_path, new_path);
            //fs::rename(new_path, cur_path);//вернул как было, чтобы каждый раз назад не менять
        }
        //10
        if (comand == "move_file")
        {
            //сначала ввод файла, потом ввод папки, в которую перемещаем
            cur_path = fs::current_path();
            std::getline(std::cin, file_name);
            std::getline(std::cin, dir_name);
            cur_path /= file_name;
            new_path = fs::current_path();
            new_path /= dir_name;
            new_path /= file_name;
            fs::rename(cur_path, new_path);
            //fs::rename(new_path, cur_path);//вернул как было, чтобы каждый раз назад не менять
        }
        //std::cin.ignore(10, '\n');
        std::getline(std::cin, comand);
    }
    return 0;
}

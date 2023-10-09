#include <iostream>
#include <string>
#include <conio.h>
#include <windows.h>
using namespace std;
HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

class ImageNode {
public:
    std::string image_name;
    ImageNode* prev;
    ImageNode* next;

    ImageNode(const std::string& name) : image_name(name), prev(nullptr), next(nullptr) {}
};

class ImageViewer {
private:
    ImageNode* current_image;
    ImageNode* first;

public:
    ImageViewer() : current_image(nullptr), first(nullptr) {}

    ~ImageViewer() {
        while (current_image) {
            ImageNode* temp = current_image;
            current_image = current_image->prev;
            delete temp;
        }
    }

    bool delete_image(const std::string& image_name);
    void add_image(const std::string& image_name);
    void insert_first_image(const std::string& image_name);
    void insert_last_image(const std::string& image_name);
    void display_current_image();
    void next_image();
    void previous_image();
    void view_all_images();
    void displayList();
    void search_image(const std::string& image_name);
};

void ImageViewer::add_image(const std::string& image_name) {

    ImageNode* new_image = new ImageNode(image_name);
    if (!first) {
        first = new_image;
        current_image = new_image;
        SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN);
        std::cout << "\nImage Added Successfully..." << std::endl;
        SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);

    } else {
        new_image->prev = current_image;
        current_image->next = new_image;
        current_image = new_image;
        SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN);
        std::cout << "\nImage Added Successfully..." << std::endl;
        SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
    }
}

void ImageViewer::insert_first_image(const std::string& image_name) {
    ImageNode* new_image = new ImageNode(image_name);
    if (!first) {
        first = new_image;
        current_image = new_image;
        SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN);
        std::cout << "\nImage Added Successfully..." << std::endl;
        SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
    } else {
        new_image->next = first;
        first->prev = new_image;
        first = new_image;
        SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN);
        std::cout << "\nImage Added Successfully..." << std::endl;
        SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
    }
}


void ImageViewer::insert_last_image(const std::string& image_name) {
    ImageNode* new_image = new ImageNode(image_name);
    if (!first) {
        first = new_image;
        current_image = new_image;
        SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN);
        std::cout << "\nImage Added Successfully..." << std::endl;
        SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
    } else {
        ImageNode* temp = first;
        while (temp->next) {
            temp = temp->next;
        }
        temp->next = new_image;
        new_image->prev = temp;
        SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN);
        std::cout << "\nImage Added Successfully..." << std::endl;
        SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
    }
}

bool ImageViewer::delete_image(const std::string& image_name) {
    ImageNode* temp = first;
    while (temp) {
        if (temp->image_name == image_name) {

            if (temp == first) {

                if (temp->next) {
                    first = temp->next;
                    first->prev = nullptr;
                } else {

                    first = nullptr;
                }
            } else {


                if (temp->prev) {
                    temp->prev->next = temp->next;
                }
                if (temp->next) {
                    temp->next->prev = temp->prev;
                }
            }

            if (temp == current_image) {
                if (temp->next) {
                    current_image = temp->next;
                } else if (temp->prev) {
                    current_image = temp->prev;
                } else {
                    current_image = nullptr;
                }
            }

            delete temp;
            return true;
        }

        temp = temp->next;
    }


    return false;
}

void ImageViewer::display_current_image() {
    if (current_image) {
        SetConsoleTextAttribute(hConsole, FOREGROUND_BLUE);
        std::cout << "Displaying Image: " << current_image->image_name << std::endl;
        SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
    } else {
        SetConsoleTextAttribute(hConsole, FOREGROUND_RED);
        std::cout << "No image to display." << std::endl;
        SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
    }
}

void ImageViewer::next_image() {
    if (current_image && current_image->next) {
        current_image = current_image->next;
        display_current_image();
    } else {
        SetConsoleTextAttribute(hConsole, FOREGROUND_RED);
        std::cout << "No next image available." << std::endl;
        SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
    }
}

void ImageViewer::previous_image() {
    if (current_image && current_image->prev) {
        current_image = current_image->prev;
        display_current_image();
    } else {
        SetConsoleTextAttribute(hConsole, FOREGROUND_RED);
        std::cout << "No previous image available." << std::endl;
        SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
    }
}

void ImageViewer::search_image(const std::string& image_name) {
    ImageNode* temp = first;
    bool found = false;
    while (temp) {
        if (temp->image_name == image_name) {
            SetConsoleTextAttribute(hConsole, FOREGROUND_BLUE);
            std::cout << "Found Image: " << temp->image_name << std::endl;
            SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
            found = true;
        }
        temp = temp->next;
    }

    if (!found) {
        SetConsoleTextAttribute(hConsole, FOREGROUND_RED);
        std::cout << "Image not found." << std::endl;
        SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
    }
}

void ImageViewer::displayList() {
    ImageNode* temp = current_image;
    int imageNumber = 1;
    while (temp && temp->prev) {
        temp = temp->prev;
    }

    while (temp) {
        SetConsoleTextAttribute(hConsole, FOREGROUND_BLUE);
        std::cout << "Image " << imageNumber << ": " << temp->image_name << std::endl;
        SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
        temp = temp->next;
        imageNumber++;
    }
}


int main() {
    ImageViewer image_viewer;

    int choice;
    p:
    system("cls");

    while (true) {
        SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_BLUE);
        std::cout << "\n                                 Image Viewer " << std::endl;
        SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
        std::cout << "\n\nImage Viewer Menu:" << std::endl;
        SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN);
        std::cout << "\n1. Add Image" << std::endl;
        std::cout << "\n2. Insert Image As First" << std::endl;
        std::cout << "\n3. Insert Image As Last" << std::endl;
        SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
        SetConsoleTextAttribute(hConsole, FOREGROUND_BLUE);
        std::cout << "\n4. Display Current Image" << std::endl;
        std::cout << "\n5. View Image List" << std::endl;
        std::cout << "\n6. Display Next Image" << std::endl;
        std::cout << "\n7. Display Previous Image" << std::endl;
        std::cout << "\n8. Search Specific Image" << std::endl;
        SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
        SetConsoleTextAttribute(hConsole, FOREGROUND_RED);
        std::cout << "\n9. Remove Image from list" << std::endl;
        std::cout << "\n10. Exit " << std::endl;
        SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
        cout << "\nYour Choice : " ;

        std::cin >> choice;

        switch (choice) {
            case 1: {
                system("cls");
                std::string image_name;
                SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_BLUE);
                std::cout << "\n                                 Image Viewer " << std::endl;
                SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
                std::cout << "\nEnter the image name: ";
                std::cin >> image_name;
                image_viewer.add_image(image_name);
                std::cout << "\nPress any key to continue...." << std::endl;
                break;
            }
            case 2: {
                system("cls");
                std::string image_name;
                SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_BLUE);
                std::cout << "\n                                 Image Viewer " << std::endl;
                SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
                std::cout << "\nEnter the image name to insert at the beginning: ";
                std::cin >> image_name;
                image_viewer.insert_first_image(image_name);
                std::cout << "\nPress any key to continue...." << std::endl;
                break;
            }
            case 3: {
                system("cls");
                std::string image_name;
                SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_BLUE);
                std::cout << "\n                                 Image Viewer " << std::endl;
                SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
                std::cout << "Enter the image name to insert at the end: ";
                std::cin >> image_name;
                image_viewer.insert_last_image(image_name);
                std::cout << "\nPress any key to continue...." << std::endl;
                break;
            }
            case 4:
                system("cls");
                SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_BLUE);
                std::cout << "\n                                 Image Viewer " << std::endl;
                SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
                image_viewer.display_current_image();
                std::cout << "\nPress any key to continue...." << std::endl;
                break;
            case 5:
                system("cls");
                SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_BLUE);
                std::cout << "\n                                 Image Viewer " << std::endl;
                SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
                image_viewer.displayList();
                std::cout << "\nPress any key to continue...." << std::endl;
                break;
            case 6:
                system("cls");
                SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_BLUE);
                std::cout << "\n                                 Image Viewer " << std::endl;
                SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
                image_viewer.next_image();
                std::cout << "\nPress any key to continue...." << std::endl;
                break;
            case 7:
                system("cls");
                SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_BLUE);
                std::cout << "\n                                 Image Viewer " << std::endl;
                SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
                image_viewer.previous_image();
                std::cout << "\nPress any key to continue...." << std::endl;
                break;
            case 8: {
                system("cls");
                std::string image_name;
                SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_BLUE);
                std::cout << "\n                                 Image Viewer " << std::endl;
                SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
                std::cout << "Enter the image name to search for: ";
                std::cin >> image_name;
                image_viewer.search_image(image_name);
                std::cout << "\nPress any key to continue...." << std::endl;
                break;
                }
            case 9: {
                system("cls");
                std::string image_name;
                SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_BLUE);
                std::cout << "\n                                 Image Viewer " << std::endl;
                SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
                std::cout << "Enter the image name to delete: ";
                std::cin >> image_name;
                if (image_viewer.delete_image(image_name)) {
                    SetConsoleTextAttribute(hConsole, FOREGROUND_RED);
                    std::cout << "Image deleted successfully." << std::endl;
                    SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
                } else {
                    SetConsoleTextAttribute(hConsole, FOREGROUND_RED);
                    std::cout << "Image not found " << std::endl;
                    SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
                }
                std::cout << "\nPress any key to continue...." << std::endl;
                break;
            }
            case 10:
                system("cls");
                SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_BLUE);
                std::cout << "Exiting the Image Viewer." << std::endl;
                SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
                return 0;
            default:
                SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_BLUE);
                std::cout << "Invalid choice. Please try again." << std::endl;
                SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
        }
        getch();
        goto p;
    }
}

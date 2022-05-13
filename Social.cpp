#include "Social.h"
#include <fstream>
#include<windows.h>
using namespace std;



Date::Date() {
    time_t t = time(nullptr);
    tm *const pTInfo = localtime(&t);
    year = 1900 + pTInfo->tm_year;
    month = pTInfo->tm_mon+1;
    day = pTInfo->tm_mday;
}

Date::Date(int d,int m,int y) {
    day = d;
    month=m;
    year = y;
}

string Date::get() {
    string full = to_string(day) + "-" + to_string(month) + "-" + to_string(year);
    return full;
}

time_t Date::getInSeconds() {
    struct tm tareekh;
    tareekh.tm_year = year-1900;
    tareekh.tm_mon = month-1;
    tareekh.tm_mday = day;
    tareekh.tm_sec = 0;
    tareekh.tm_min = 0;
    tareekh.tm_hour = 0;
    return mktime(&tareekh);
}

Entity::Entity() {
    id = "";
    name = "";
    posts=nullptr;
    size_posts=0;
    sharedPosts=nullptr;
    sizeOfSharedPosts=0;
}

Entity::Entity(string id, string name) {
    this->id = id;
    this->name = name;
    posts=nullptr;
    size_posts=0;
    sharedPosts=nullptr;
    sizeOfSharedPosts=0;
}

string Entity::getId() {
    return this->id;
}

string Entity::getName() {
    return name;
}

void Entity::createPost(Post* &obj) {
    SocialNetwork::extendArr(posts,size_posts);
    posts[size_posts-1] = obj;
}

void Entity::sharePost(Post* &obj) {
    SocialNetwork::extendArr(sharedPosts,sizeOfSharedPosts);
    sharedPosts[sizeOfSharedPosts-1] = obj;
}

Entity::~Entity() {
        delete [] sharedPosts;
        sharedPosts = nullptr;
        for (int i=0;i<commentsSize;i++) {
            delete [] comments[i];
        }
        comments = nullptr;
        for (int i=0;i<size_posts;i++) {
            delete [] posts[i];
        }
        posts = nullptr;
}

User::User(string id, string name) : Entity(id, name) {
    friends = 0;
    friendsList = nullptr;
    likedPages = nullptr;
    sizeOfFriendsList = 0;
    size_likedPages = 0;
};

void User::receiveFriend(Entity*& obj) {
    SocialNetwork::extendArr(friendsList, sizeOfFriendsList);
    friendsList[sizeOfFriendsList - 1] = obj;
}

void User::receiveLikedPage(Entity*& obj) {
    SocialNetwork::extendArr(likedPages, size_likedPages);
    likedPages[size_likedPages - 1] = obj;
}

void Page::ViewPage(){
    for (int i = 0; i < size_posts; i++)
    {
        posts[i]->display(); cout << endl;
    }
    cout << "-------------------------------------------------------------------------------------------------------------\n";

}

void Page::receiveLikedPage(Entity* &obj) {
    SocialNetwork::extendArr(pageLikes, likes);
    pageLikes[likes - 1] = obj;
}

Page::~Page() {
        delete [] pageLikes;
}
Post::Post() {
    likes = 0;
    text = "";
    createdBy = nullptr;
    comments = nullptr;
    createdAt = Date();
}

string Post::getId() {
    return id;
}

string Post::getContent() {
    return text;
}

void Post::addComment(Comment* obj) {
    SocialNetwork::extendArr(comments,commentsSize);
    comments[commentsSize - 1] = obj;

}

Post::Post(string id, string text, Entity* &createdBy, Date createdAt) {
    this->id = id;
    this->text = text;
    this->createdAt = Date(createdAt);
    this->createdBy = createdBy;
    likes = 0;
    likesBy = nullptr;
}

void Post::addLike(Entity* LikeBy) {
    SocialNetwork::extendArr(likesBy,likes);
    likesBy[likes-1] = LikeBy;
}

void Post::showLikesArr(){
    for (int i = 0; i < likes; i++)
    {
        cout << likesBy[i]->getId() << " - " << likesBy[i]->getName() << endl;
    }
cout << "-------------------------------------------------------------------------------------------------------------\n";
}

void Post::display() {
    cout << "--- " << this->createdBy->getName() << " shared \"" << this->text << "\"\n";
    for (int i=0;i<this->commentsSize;i++) {
        this->comments[i]->print();
    }
}

Activity::Activity(string id, string text, Entity*& createdBy,string type,string value, Date createdAt) : Post(id, text, createdBy, createdAt) {
    this->type = type;
    this->value = value;
}

void Activity::display() {
    cout << "--- " << this->createdBy->getName() << " is \"" << this->type << " " << this->value << "\"\n";
    cout << "\"" << this->text << "\"\n";
    for (int i=0;i<this->commentsSize;i++) {
        this->comments[i]->print();
    }    
}

Comment::Comment(string text, string id,Entity* &createdBy) {
    this->id = id;
    this->Text = text;
    this->createdBy = createdBy;
}

void Comment::print() {
   SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 8);
    cout << "\t" << this->createdBy->getName() << " wrote: \"" << this->Text << "\"" <<endl;
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
}

void User::showLikedPages() {
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12);
    cout << "Command: View\tView Liked Pages\n";
    cout << "-------------------------------------------------------------------------------------------------------------\n";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
    cout << this->name << "- Liked Pages\n\n\n";
    for(int i = 0; i < size_likedPages; i++) {
        cout << likedPages[i]->getId() << " - " << likedPages[i]->getName() << endl;
    }
SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12);
    cout << "-------------------------------------------------------------------------------------------------------------\n";
SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
}

void User::showFriendList(){
SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 11);
cout << "Command: View\tFriend List\n";
cout << "-------------------------------------------------------------------------------------------------------------\n";
SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
cout << this->name << "- Friend List\n";
for(int i = 0; i < sizeOfFriendsList; i++)
{
    cout << friendsList[i]->getId() << " - " << friendsList[i]->getName() << endl;
}
SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 11);
cout << "-------------------------------------------------------------------------------------------------------------\n";    
SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
}

void User::showHome(Date date){
SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 6);
    cout << "Command:\tView Home\n";
    cout << "-------------------------------------------------------------------------------------------------------------\n";
SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
    cout << this->name << "- Home Page\n\n";
    for (int i=0;i<this->sizeOfFriendsList;i++) {
        Entity* temp = this->friendsList[i];
        for (int i=0;i<temp->size_posts;i++) {
            Post* tmp= temp->posts[i];
            double seconds = difftime(date.getInSeconds(),tmp->createdAt.getInSeconds());
            double days= (seconds/3600)/24;
            if (days <2 && days>=0) {
                tmp->display();
                cout << endl;
            }
        }
    }

    for (int i=0;i<this->size_likedPages;i++) {
        Entity* temp = this->likedPages[i];
        for (int i=0;i<temp->size_posts;i++) {
            Post* tmp= temp->posts[i];
            double seconds = difftime(date.getInSeconds(),tmp->createdAt.getInSeconds());
            double days= (seconds/3600)/24;
            if (days <2 && days>=0) {
                tmp->display();
                cout << endl;
            }
        }
    }
SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 6);
    cout << "-------------------------------------------------------------------------------------------------------------\n";
SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
}

void User::viewTimeLine(Date date){
SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 9);
    cout << "Command:\tView Timeline\n";
    cout << "-------------------------------------------------------------------------------------------------------------\n";
SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7); 
    cout << this->name << "- Timeline\n\n";
    
    for (int i=0;i<this->size_posts;i++) {
        Post* temp = this->posts[i];
        double seconds = difftime(date.getInSeconds(),temp->createdAt.getInSeconds());
        double days= (seconds/3600)/24;
        if (days <2) {
            temp->display();
            cout << endl;
        }
    }

    for (int i=0;i<this->sizeOfSharedPosts;i++) {
        Post* temp = this->sharedPosts[i];
        double seconds = difftime(date.getInSeconds(),temp->createdAt.getInSeconds());
        double days= (seconds/3600)/24;
        if (days <2) {
            temp->display();
            cout << endl;
        }
    }
SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 9);
    cout << "-------------------------------------------------------------------------------------------------------------\n";
SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
}

void SocialNetwork::RUN_DATA() 
{
    ifstream socialPages("Pages.txt");
    if (socialPages.is_open()) {
        socialPages >> sizeOfPages;
        socialPagesArr = new Entity * [sizeOfPages];
        for (int i = 0; !socialPages.eof(); i++) 
        {
            string id;
            string temp;
            char t;
            socialPages >> id;
            while(1) 
            {
                socialPages.get(t);
                if (t == '\t'){ 
                    break;
                }
            }
            getline(socialPages, temp, '\n');
            socialPagesArr[i] = new Page(id, temp);
        }
    }
    else {
        cout << "Cannot Open Pages.txt\n";
    }

    ifstream usersFile("Users.txt");
    if (usersFile.is_open()) {
        usersFile >> sizeOfUsers;
        socialUsersArr = new Entity * [sizeOfUsers];
        for (int i = 0; i < sizeOfUsers; i++) 
        {
            string uID,NAME,FirstName, LastName;
            usersFile >> uID;
            usersFile >> FirstName >> LastName;
            NAME = FirstName + " " + LastName;
            string space;
            getline(usersFile,space,'\n');
            socialUsersArr[i] = new User(uID, NAME);
        }
        usersFile.close();

        ifstream usersFile2("Users.txt");
        usersFile2 >> sizeOfUsers;
        for (int i = 0; i < sizeOfUsers; i++) 
        {
            string tmp;
            usersFile2 >> tmp;
            usersFile2 >> tmp >> tmp;
            do {
                usersFile2 >> tmp;
                if (tmp == "-1")
                {
                    break;
                }
                int item = SocialNetwork::checkItem(socialUsersArr, tmp, sizeOfUsers);
                socialUsersArr[i]->receiveFriend(socialUsersArr[item]);
            } while (1);

            do {
                usersFile2 >> tmp;
                if (tmp == "-1")
                {
                    break;
                }
                int item = SocialNetwork::checkItem(socialPagesArr,tmp,sizeOfPages);
                socialUsersArr[i]->receiveLikedPage(socialPagesArr[item]);
                socialPagesArr[item]->receiveLikedPage(socialUsersArr[i]);
            } while (1);
        }
    }
    else {
        cout << "Cannot Open Users.txt\n";
    }

    fstream socialPosts("Posts.txt");
    if (socialPosts.is_open()) {
        sizeOfPosts;
        socialPosts >> sizeOfPosts;
        socialsPostsArr = new Post * [sizeOfPosts];
        int detector=0;

        string titles[5] = {"Simple","feeling","Thinking About","Making","Celebrating"};
    
        while (detector<sizeOfPosts) 
        {
            bool isActivity = false;
            string id,text,owner;
            socialPosts >> id;
            int d,m,y;
            socialPosts >> d >> m >> y;
            Date postedOn(d,m,y);
            socialPosts.ignore();
            getline( socialPosts , text,'\n');
            string ACTIVITY_EXPLAIN, ACTIVITY_TITLE;
            int NUMERIC_ACTIVITY;
            socialPosts >> NUMERIC_ACTIVITY;
            ACTIVITY_TITLE = titles[NUMERIC_ACTIVITY];

            if (NUMERIC_ACTIVITY !=0) 
            {
                isActivity = 1;
                socialPosts.ignore();
                getline(socialPosts,ACTIVITY_EXPLAIN,'\n');
            }

            socialPosts >> owner;
            int item = SocialNetwork::checkItem(owner[0] == 'p' ? socialPagesArr : socialUsersArr,owner ,owner[0] == 'p' ? sizeOfPages : sizeOfUsers);
            Entity* creator = owner[0] == 'p' ? socialPagesArr[item] : socialUsersArr[item];
            if (!isActivity) 
            {
                socialsPostsArr[detector] = new Post(id, text, creator, postedOn);
            }
            else {
                socialsPostsArr[detector] = new Activity(id, text, creator,ACTIVITY_TITLE,ACTIVITY_EXPLAIN, postedOn);
            }

            if (owner[0] == 'p') 
            {
                socialPagesArr[item]->createPost(socialsPostsArr[detector]);
            }
            else {
                socialUsersArr[item]->createPost(socialsPostsArr[detector]);
            }

            string temp;
            do {
                socialPosts >> temp;
                if (temp == "-1")
                {
                    break;
                }
                int item = SocialNetwork::checkItem(temp[0] == 'p' ? socialPagesArr : socialUsersArr,temp,temp[0] == 'p' ? sizeOfPages : sizeOfUsers);
                socialsPostsArr[detector]->addLike(temp[0] == 'p' ? socialPagesArr[item] : socialUsersArr[item]);
            } while (1);
            detector++;
        }
    }
    else {
        cout << "Unable to Open Posts.txt\n";
    }

    fstream socialComments("Comments.txt");

    if (socialComments.is_open()) {
        socialComments >> comments_size;
        commentArr = new Comment * [comments_size];
        int i=0;
        while (i<comments_size) 
        {
            string id,text,post,owner;
            socialComments >> id;
            socialComments >> post;
            socialComments >> owner;
            socialComments.ignore();
            getline(socialComments,text,'\n');
            int item = SocialNetwork::checkItem(socialsPostsArr,post ,sizeOfPosts);
            int item2 = SocialNetwork::checkItem(owner[0]== 'p' ? socialPagesArr : socialUsersArr,owner ,owner[0]== 'p' ? sizeOfPages : sizeOfUsers);
            commentArr[i] = new Comment(text,id,owner[0]== 'p' ? socialPagesArr[item2] : socialUsersArr[item2]);
            socialsPostsArr[item]->addComment(commentArr[i]);
            i++;
        }
    }
    else {
        cout << "Unable to Open socialComments.txt\n";
    }
}

void SocialNetwork::globalSearch(string query) 
{
    bool p= false,pp= false,u = false;
    for (int i=0;i<sizeOfPosts;i++) {
        Post* temp = socialsPostsArr[i];
        if (temp->getContent().find(query) !=string::npos) 
        {
            if (!p) {
                cout << "Posts:\n";
                p=true;
            }
            temp->display();
            cout << endl;
        }
    }

    cout << endl;

    for (int i=0;i<sizeOfUsers;i++) {
        Entity* temp = socialUsersArr[i];
        if (temp->getName().find(query) !=string::npos) 
        {
            if (!u) {
                cout << "Users:\n";
                u=true;
            }
            cout << "--- " << temp->getId() << "-" << temp->getName() << endl;
        }
    }

    cout << endl;


    for (int i=0;i<sizeOfPages;i++) {
        Entity* temp = socialPagesArr[i];
        if (temp->getName().find(query) !=string::npos) 
        {
            if (!pp) {
                cout << "Pages:\n";
                pp=true;
            }
            cout << "--- " << temp->getId() << "-" << temp->getName() << endl;
        }
    }

    cout << endl;
}

void SocialNetwork::OUTPUT_DATA()
{
    string cur = "u7";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 5);
    cout << "Command:\tSet CURRENT USER "<< cur <<" \n";
    int selectedOne = SocialNetwork::checkItem(socialUsersArr,cur,sizeOfUsers);
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 4);
    cout << socialUsersArr[selectedOne]->getName() << " set as CURRENT USER\n";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 6);
    cout << "Command:\tSet current System Date 15 11 2017\n";
    date =  Date(15,11,2017);
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 3);
    cout << "System Date " << date.get() << endl;
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);

    socialUsersArr[selectedOne]->showFriendList();
    socialUsersArr[selectedOne]->showLikedPages();
    socialUsersArr[selectedOne]->showHome(date);
    socialUsersArr[selectedOne]->viewTimeLine(date);


    int itemPost = SocialNetwork::checkItem(socialsPostsArr,"post5",sizeOfPosts);
    socialsPostsArr[itemPost]->showLikesArr();
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 5);
    cout << "Command:\tLikePost (" << socialsPostsArr[itemPost]->getId() << ")" <<endl;
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
    socialsPostsArr[itemPost]->addLike(socialUsersArr[selectedOne]);
    socialsPostsArr[itemPost]->showLikesArr();


    string text = "Good Luck for your Result. The latest One";
    cout << "Command:\tPostComment(post4, " << text << ")\n";
    int postitem2 = SocialNetwork::checkItem(socialsPostsArr,"post4",sizeOfPosts);
    SocialNetwork::extendArr(commentArr,comments_size);
    string id = "c" + to_string(comments_size);
    commentArr[comments_size-1] = new Comment(text,id,socialUsersArr[selectedOne]);
    socialsPostsArr[postitem2]->addComment(commentArr[comments_size-1]);

    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 6);
    cout << "Command:\tViewPost(post4)\n\n";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
    socialsPostsArr[postitem2]->display();
    int Pageitem = SocialNetwork::checkItem(socialPagesArr,"p1",sizeOfPages);
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 6);
    cout << "-------------------------------------------------------------------------------------------------------------\n";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 3);
    cout << "Command: ViewPage(p1)\n"; 
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
    socialPagesArr[Pageitem]->ViewPage();
    text = "Thanks for the Wishes";

    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 5);
    cout << "\nCommand:\tPostComment(post8, " << text << ")\n";
    postitem2 = SocialNetwork::checkItem(socialsPostsArr,"post8",sizeOfPosts);
    SocialNetwork::extendArr(commentArr,comments_size);
    id = "c" + to_string(comments_size);
    commentArr[comments_size-1] = new Comment(text,id,socialUsersArr[selectedOne]);
    socialsPostsArr[postitem2]->addComment(commentArr[comments_size-1]);
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 2);
    cout << "Command:\tViewPost(post8)\n\n";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
    socialsPostsArr[postitem2]->display();

    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 6);
    cout << "\nCommand:\tSharePost(post5)\n";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
    socialUsersArr[selectedOne]->sharePost(socialsPostsArr[itemPost]);
    socialUsersArr[selectedOne]->viewTimeLine(date);

    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 4);
    cout << "-------------------------------------------------------------------------------------------------------------\n";
    cout << "\nCommand:\tSearch(\"Birthday\")\n";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 11);
    globalSearch("Birthday");
    cout << "-------------------------------------------------------------------------------------------------------------\n\n\n";
    cout << "-------------------------------------------------------------------------------------------------------------\n";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 4);
    cout << "\nCommand:\tSearch(\"Ali\")\n";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 6);
    globalSearch("Ali");
    cout << "-------------------------------------------------------------------------------------------------------------\n";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);  
    cout << endl << endl << endl;
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
    cout << "-------------------------------------------------------------------------------------------------------------\n";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 9);
    cout << "\t\t\tOOP Final Project By:\n\t\t\t\tMuhammad Meeran 20L-2111\n\t\t\t\tFaraz Majid 20L-1162\n";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
    cout << "-------------------------------------------------------------------------------------------------------------\n";

}

SocialNetwork::~SocialNetwork(){
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 4);
    delete commentArr;
    cout << "Comments Deleted\n";
    delete socialUsersArr;
    cout << "User Deleted\n";
    delete socialPagesArr;
    cout << "Pages Deleted\n";
    delete socialsPostsArr;
    cout << "Posts Deleted\n";
}

int main() {
    SocialNetwork Facebook;
    Facebook.RUN_DATA();
    Facebook.OUTPUT_DATA();
    system("pause");
}
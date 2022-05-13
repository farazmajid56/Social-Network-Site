#include <string>
#include <ctime>
#include <iostream>
using namespace std;


//Forward Declarations
class Post;
class Comment;
class User;
//End of Forward Declarations

class Date {
    int day,month,year;
public:
    Date();
    Date(int d,int m,int y);
    string get();
    time_t getInSeconds();
};


class Entity {
protected:
    string id;
    string name;
    Post ** sharedPosts;
    int sizeOfSharedPosts;
    Comment** comments;
    int commentsSize;
    Date createdAt;
public:
    Entity();
    Entity(string id, string name);
    Post **posts;
    int size_posts;
    void virtual addComment(string id, string text, string postID) {};
    void virtual receiveFriend(Entity*& obj) {}
    void virtual receiveLikedPage(Entity*& obj) {}
    void createPost(Post* &obj);
    void sharePost(Post* &obj);
    virtual void showFriendList() {}
    string getId();
    string getName();
    virtual void showLikedPages() {}
    virtual void showHome(Date obj){}
    virtual void viewTimeLine(Date date) {}
    virtual void ViewPage() {}
    ~Entity();
};


class Page :public Entity {
    int likes;
    Entity** pageLikes;
public:
    Page(string id, string name) : Entity(id, name) {
        likes=0;
        pageLikes = nullptr;
    };
    ~Page();
    void receiveLikedPage(Entity* & obj);
    void ViewPage();
};


class User :public Entity {
    int friends;
    Entity** friendsList;
    Entity** likedPages;
    int sizeOfFriendsList;
    int size_likedPages;
public:
    User(string id, string name);
    void receiveFriend(Entity*& obj);
    void receiveLikedPage(Entity*& obj);
    void showFriendList();
    void showLikedPages();
    void showHome(Date date);
    void viewTimeLine(Date date);
    ~User() {
        delete [] friendsList;
        delete [] likedPages;
        friends = 0;
        sizeOfFriendsList=0;
        size_likedPages=0;
    }
};


class Post {
protected:
    int likes;
    Entity** likesBy;
    string text;
    Entity* createdBy;
    Comment** comments;
    int commentsSize = 0;
    Date createdAt;
    string id;

public:
    Post();
    string getId();
    string getContent();
    void addComment(Comment* obj);
    Post(string id, string text, Entity* &createdBy,Date createdAt);
    void addLike(Entity* LikeBy);
    void showLikesArr();
    void virtual display();
    friend User;
    friend Page;
    ~Post() {
        delete [] likesBy;
        for (int i=0;i<commentsSize;i++) {
            delete [] comments[i];
        }
    }
};


class Activity : public Post {
    string type;
    string value;
public:
    Activity(string id, string text, Entity*& createdBy,string type,string value, Date createdAt);
    void display();
};


class Comment {
    string Text;
    Date createdAt;
    string id;
    Entity* createdBy;
public:
    Comment() {
        Text= "";
        time_t myTime= time(0);
        createdAt = Date();
        id="";
        createdBy=nullptr;        
    }
    Comment(string text, string id,Entity* &createdBy);
    void print();
};


class SocialNetwork {
    Date date;
    Entity** socialPagesArr;
    Entity** socialUsersArr;
    Post** socialsPostsArr;
    Comment** commentArr;
    int sizeOfPages, sizeOfUsers,sizeOfPosts,comments_size;
public:

    void RUN_DATA();
    void globalSearch(string query);
    void OUTPUT_DATA();
    ~SocialNetwork();
    template <class T>
    static int checkItem(T** Array, string ID, int SIZE) {

        for (int i = 0; i < SIZE; i++) {
            if (Array[i]->getId() == ID) {
                return i;
            }
        }
        return -1;
    }

    template<class T>
    static void extendArr(T** &Array, int& SIZE) {
        SIZE++;
        T** longArr = new T * [SIZE];
        for (int i = 0; i < SIZE - 1; i++) {
            longArr[i] = Array[i];
        }
        Array = longArr;
    }

};
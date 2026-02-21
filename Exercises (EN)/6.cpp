#include<iostream>
#include<cstdio>
#include<cstring>
using namespace std;

class Camera {
protected:
    char manufacturer[21];
    char model[21];
    int year;
    float resolution;
public:
    Camera() {
        strcpy(manufacturer, "");
        strcpy(model, "");
        year = -1;
        resolution = -1;
    }

    Camera(char *manufacturer, char *model, int year, float resolution) {
        strcpy(this->manufacturer, manufacturer);
        strcpy(this->model, model);
        this->year = year;
        this->resolution = resolution;
    }

    Camera(const Camera &n) {
        strcpy(this->manufacturer, n.manufacturer);
        strcpy(this->model, n.model);
        this->year = n.year;
        this->resolution = n.resolution;
    }

    Camera& operator=(const Camera &n) {
        if (this != &n) {
            strcpy(this->manufacturer, n.manufacturer);
            strcpy(this->model, n.model);
            this->year = n.year;
            this->resolution = n.resolution;
        }
        return *this;
    }

    virtual ~Camera() {}

    virtual double price() = 0;
    virtual double rentalPrice(int days) = 0;

    bool operator<(Camera &n) {
        return this->price() < n.price();
    }

    friend ostream& operator<<(ostream& out, const Camera& c) {
        return out << c.model;
    }

    friend ostream& operator<<(ostream& out, const Camera* c) {
        return out << *c;
    }
};

class PhotoCamera : public Camera {
private:
    bool raw;
public:
    PhotoCamera() : Camera() {
        raw = false;
    }

    PhotoCamera(char *manufacturer, char *model, int year, float resolution, bool raw)
        : Camera(manufacturer, model, year, resolution) {
        this->raw = raw;
    }

    PhotoCamera(const PhotoCamera &n) : Camera(n) {
        this->raw = n.raw;
    }

    PhotoCamera& operator=(const PhotoCamera &n) {
        if (this != &n) {
            Camera::operator=(n);
            this->raw = n.raw;
        }
        return *this;
    }

    double price() override {
        double sum = 100 + resolution * 20;
        if (raw) {
            sum += 50;
        }
        return sum;
    }

    double rentalPrice(int days) override {
        double dailyRate = price() / 100.0;
        if (days > 7) {
            dailyRate *= 0.8;
        }
        return days * dailyRate;
    }
};

class VideoCamera : public Camera {
private:
    int max_video;
public:
    VideoCamera() : Camera() {
        max_video = -1;
    }

    VideoCamera(char *manufacturer, char *model, int year, float resolution, int max_video)
        : Camera(manufacturer, model, year, resolution) {
        this->max_video = max_video;
    }

    VideoCamera(const VideoCamera &n) : Camera(n) {
        this->max_video = n.max_video;
    }

    VideoCamera& operator=(const VideoCamera &n) {
        if (this != &n) {
            Camera::operator=(n);
            this->max_video = n.max_video;
        }
        return *this;
    }

    double price() override {
      double suma = resolution * 80;
if ((max_video / 60) > 60) { // apply the 40% only if video is longer than 60 minutes
    suma *= 1.4;
}
return suma;
    }

    double rentalPrice(int days) override {
        double dailyRate = price() / 100.0;
        if (days > 7) {
            dailyRate *= 0.8;
        }
        return days * dailyRate;
    }
};

class FilmCamera : public Camera {
private:
    int fps;
public:
    FilmCamera() : Camera() {
        fps = -1;
    }

    FilmCamera(char *manufacturer, char *model, int year, float resolution, int fps)
        : Camera(manufacturer, model, year, resolution) {
        this->fps = fps;
    }

    FilmCamera(const FilmCamera &n) : Camera(n) {
        this->fps = n.fps;
    }

    FilmCamera& operator=(const FilmCamera &n) {
        if (this != &n) {
            Camera::operator=(n);
            this->fps = n.fps;
        }
        return *this;
    }

    double price() override {
        double base = 5000;
        if (fps > 30) {
            base += (fps - 30) * 5000;
        }
        return base;
    }

    double rentalPrice(int days) override {
        if (fps > 60) {
            return days * 1000;
        }
        return days * 500;
    }
};

double production(Camera **niza, int n, int days) {
    double total = 0;
    for (int i = 0; i < n; ++i) {
        total += niza[i]->rentalPrice(days);
    }
    return total;
}

Camera* mostExpensiveCamera(Camera **niza, int n) {
    int index = 0;
    for (int i = 1; i < n; ++i) {
        if (niza[i]->price() > niza[index]->price()) {
            index = i;
        }
    }
    return niza[index];
}

int main(int argc, char *argv[])
{
    char model[20], producer[20];
    int year, length, fps, n;
    float resolution;
    bool raw;
    int t;

    Camera *c[10];

    cin >> n;

    for (int i = 0; i < n; ++i) {
        cin >> t;

        if (t == 1) {
            cin >> producer >> model >> year >> resolution;
            cin >> raw;
            c[i] = new PhotoCamera(producer, model, year, resolution, raw);
        }
        else if (t == 2) {
            cin >> producer >> model >> year >> resolution;
            cin >> length;
            c[i] = new VideoCamera(producer, model, year, resolution, length);
        }
        else if (t == 3) {
            cin >> producer >> model >> year >> resolution;
            cin >> fps;
            c[i] = new FilmCamera(producer, model, year, resolution, fps);
        }
    }

    int days;
    cin >> days;

    cout << "Price of production is: " << production(c, n, days);
    cout << "\nMost expensive camera used in production is: " << mostExpensiveCamera(c, n);

    return 0;
}

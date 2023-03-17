typedef struct s_keyboard {
    bool keyState[128];
    bool keyPressed[128];
    bool keyReleased[128];
} t_keyboard;

typedef struct s_button {
    double xAxis;
    double yAxis;
    bool b1;
    bool b2;
    bool b3;
    bool b4;
} t_button;

class IGame {
    public:
        void loadGame(std::string &libName);
        double capFps(double fps);
        bool *getMousePos(bool *coords);
        bool *getMouseButton(bool *mouseButtons);
        bool *getKeyboard(bool *keys);
        bool *getButtons(t_button *buttons);
        void run();
};

class IShape {
    public:
        void draw(void);
        // IShape *getShape(void);
        void setColor(int r, int g, int b);
        void setPosition(double x, double y);
        void setRotation(double rad);
        void setScale(double rad);
        void setSize(double w, double h);
};

class IGraphics {
    public:
        void loadLib(std::string &libName);
        void fill(int color);
        void drawShape(IShape *shape);
        void drawTile(double x, double y, int color);
        void drawTileLine(double x1, int y1, int x2, int y2, int color);
        void drawTileRect(int x1, int y1, int x2, int y2, int color);
        void drawTileCircle(int x1, int y1, int x2, int y2, int color);
        void display(int x1, int y1, int x2, int y2, int color);

};

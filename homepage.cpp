#include "Homepage.h"

// ══════════════════════════════════════════════════════════════
//  Global stylesheet — applied to the whole window.
//  Children inherit and can override via objectName selectors.
// ══════════════════════════════════════════════════════════════
static const char* GLOBAL_QSS = R"(

    /* Base */
    QWidget {
        font-family: 'Segoe UI';
        font-size: 12pt;
        color: #3C6291;
        background: transparent;
    }

    /* Top bar */
    #topBar {
        background: #FFFFFF;
        border-bottom: 1px solid #E4E7F0;
    }

    /* Left nav */
    #leftNav {
        background: #FFFFFF;
        border-right: 1px solid #E4E7F0;
    }

    /* Main content area */
    #mainContent { background: #F8F9FC; }

    /* Bottom stats bar */
    #bottomBar {
        background: #FFFFFF;
        border-top: 1px solid #3C6291;
    }

    /* White cards (Daily Quest, small cards) */
    #whiteCard {
        background: #FFFFFF;
        border: 1px solid #3C6291;
        border-radius: 12px;
    }

    /* Start Game hero card */
    #startCard {
        background: qlineargradient(x1:0, y1:0, x2:1, y2:0,
                    stop:0 #3C6291, stop:1 #4D71A1FF);
        border-radius: 12px;
    }

    /* Timer / coin chips */
    #chip {
        background: #F8F9FC;
        border: 1px solid #E4E7F0;
        border-radius: 14px;
    }

    /* Upgrade button */
    QPushButton#upgradeBtn {
        background: #3C6291;
        color: white;
        border: none;
        border-radius: 8px;
        font-size: 10pt;
        font-weight: bold;
        padding: 8px 16px;
    }
    QPushButton#upgradeBtn:hover { background: #1D3CB4; }

    /* Nav buttons */
    QPushButton#navBtn {
        background: transparent;
        border: none;
        border-radius: 8px;
        color: #3C6291;
        font-size: 10pt;
        text-align: left;
        padding-left: 10px;
    }
    QPushButton#navBtn:hover { background: #EEF1FB; color: #4d71a1; }

    /* Check Progress link */
    QPushButton#progressBtn {
        background: transparent;
        border: none;
        color: #3C6291;
        font-weight: bold;
        font-size: 10pt;
        text-align: left;
        padding: 0;
    }
    QPushButton#progressBtn:hover { color: #1D3CB4; }

)";

// ══════════════════════════════════════════════════════════════
//  Constructor
// ══════════════════════════════════════════════════════════════
Homepage::Homepage(QWidget* parent) : QWidget(parent)
{
    setWindowTitle("CrossWordQuest");
    setMinimumSize(1100, 680);
    resize(1120, 720);
    setStyleSheet(GLOBAL_QSS);

    QVBoxLayout* root = new QVBoxLayout(this);
    root->setContentsMargins(0, 0, 0, 0);
    root->setSpacing(0);

    // Top bar
    root->addWidget(buildTopBar());

    // Middle row: left nav + main content
    QHBoxLayout* middle = new QHBoxLayout();
    middle->setContentsMargins(0, 0, 0, 0);
    middle->setSpacing(0);
    middle->addWidget(buildLeftNav());
    middle->addWidget(buildMainContent(), 1);

    QWidget* middleWidget = new QWidget();
    middleWidget->setLayout(middle);
    middleWidget->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    root->addWidget(middleWidget, 1);

    // Bottom stats bar
    root->addWidget(buildBottomStats());
}

// ══════════════════════════════════════════════════════════════
//  TOP BAR
// ══════════════════════════════════════════════════════════════
QWidget* Homepage::buildTopBar()
{
    QWidget* bar = new QWidget();
    bar->setObjectName("topBar");
    bar->setFixedHeight(52);

    QHBoxLayout* lay = new QHBoxLayout(bar);
    lay->setContentsMargins(18, 0, 18, 0);
    lay->setSpacing(0);

    // Logo icon — MDL2 glyph in a blue rounded square
    QLabel* logoIcon = new QLabel(QString::fromUtf8(ICO_GRID));
    logoIcon->setFont(mdl2(13));
    logoIcon->setFixedSize(30, 30);
    logoIcon->setAlignment(Qt::AlignCenter);
    logoIcon->setStyleSheet("background:#3C6291; color:white; border-radius:6px;");

    // Logo text
    QLabel* logoText = new QLabel("CrossWordQuest");
    logoText->setFont(segoe(11, true));
    logoText->setStyleSheet("color:#1C1E2E;");

    // Nav tabs
    QLabel* tabLevels      = makeNavTab("Levels",      true);
    QLabel* tabLeaderboard = makeNavTab("Leaderboard", false);
    QLabel* tabSettings    = makeNavTab("Settings",    false);

    // Chips
    QWidget* timerChip = makeIconChip(ICO_CLOCK, "50:46");
    QWidget* coinChip  = makeIconChip(ICO_STAR,  "1,250");

    // Avatar circle
    //AvatarWidget* avatar = new AvatarWidget();

    lay->addWidget(logoIcon);
    lay->addSpacing(8);
    lay->addWidget(logoText);
    lay->addSpacing(40);
    lay->addWidget(tabLevels);
    lay->addSpacing(4);
    lay->addWidget(tabLeaderboard);
    lay->addSpacing(4);
    lay->addWidget(tabSettings);
    lay->addStretch();
    lay->addWidget(timerChip);
    lay->addSpacing(8);
    lay->addWidget(coinChip);
    lay->addSpacing(14);
    //lay->addWidget(avatar);

    return bar;
}

QLabel* Homepage::makeNavTab(const QString& text, bool active)
{
    QLabel* lbl = new QLabel(text);
    lbl->setFont(segoe(10, active));
    lbl->setCursor(Qt::PointingHandCursor);
    lbl->setContentsMargins(14, 16, 14, 16);
    lbl->setStyleSheet(active
                           ? "color:#4d71a1; border-bottom:3px solid #4d71a1;"
                           : "color:#7B82A3;");
    return lbl;
}

QWidget* Homepage::makeIconChip(const QString& icon, const QString& text)
{
    QWidget* chip = new QWidget();
    chip->setObjectName("chip");
    chip->setFixedHeight(30);

    QHBoxLayout* lay = new QHBoxLayout(chip);
    lay->setContentsMargins(10, 0, 10, 0);
    lay->setSpacing(5);

    QLabel* ico = new QLabel(QString::fromUtf8(icon.toUtf8()));
    ico->setFont(mdl2(10));
    ico->setStyleSheet("color:#4d71a1;");

    QLabel* lbl = new QLabel(text);
    lbl->setFont(segoe(9, true));
    lbl->setStyleSheet("color:#7B82A3;");

    lay->addWidget(ico);
    lay->addWidget(lbl);
    return chip;
}

// ══════════════════════════════════════════════════════════════
//  LEFT NAV
// ══════════════════════════════════════════════════════════════
QWidget* Homepage::buildLeftNav()
{
    QWidget* nav = new QWidget();
    nav->setObjectName("leftNav");
    nav->setFixedWidth(205);

    QVBoxLayout* lay = new QVBoxLayout(nav);
    lay->setContentsMargins(16, 18, 16, 16);
    lay->setSpacing(2);

    // Player info
    QLabel* name = new QLabel("Pro Solver");
    name->setFont(segoe(10, true));
    name->setStyleSheet("color:#4d71a1;");

    QLabel* level = new QLabel(QString::fromUtf8("Level 43  \u00B7  Grandmaster"));
    level->setFont(segoe(9));
    level->setStyleSheet("color:#7B82A3;");

    QFrame* divider = new QFrame();
    divider->setFrameShape(QFrame::HLine);
    divider->setStyleSheet("color:#E4E7F0;");

    lay->addWidget(name);
    lay->addWidget(level);
    lay->addSpacing(8);
    lay->addWidget(divider);
    lay->addSpacing(6);

    // Nav items
    lay->addWidget(makeNavBtn(ICO_HOME,     "Home",            true));
    lay->addWidget(makeNavBtn(ICO_PUZZLE,   "Puzzles",         false));
    lay->addWidget(makeNavBtn(ICO_CALENDAR, "Daily Challenge", false));
    lay->addWidget(makeNavBtn(ICO_TROPHY,   "Achievements",    false));
    lay->addWidget(makeNavBtn(ICO_SHOP,     "Store",           false));

    lay->addSpacing(16);

    // Upgrade button
    QPushButton* upgrade = new QPushButton("Upgrade to Premium");
    upgrade->setObjectName("upgradeBtn");
    upgrade->setFixedHeight(38);
    upgrade->setCursor(Qt::PointingHandCursor);
    lay->addWidget(upgrade);

    lay->addStretch();

    lay->addWidget(makeNavBtn(ICO_HELP, "Help", false));
    lay->addWidget(makeNavBtn(ICO_EXIT, "Exit", false));

    return nav;
}

QPushButton* Homepage::makeNavBtn(const QString& icon,
                                  const QString& label,
                                  bool active)
{
    QPushButton* btn = new QPushButton();
    btn->setObjectName("navBtn");
    btn->setFixedHeight(38);
    btn->setCursor(Qt::PointingHandCursor);
    btn->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
    btn->setFlat(true);

    // Layout two labels inside the button
    QHBoxLayout* lay = new QHBoxLayout(btn);
    lay->setContentsMargins(10, 0, 10, 0);
    lay->setSpacing(8);

    // MDL2 icon label
    QLabel* ico = new QLabel(QString::fromUtf8(icon.toUtf8()));
    ico->setFont(mdl2(13));
    ico->setFixedWidth(20);
    ico->setAlignment(Qt::AlignCenter);
    ico->setAttribute(Qt::WA_TransparentForMouseEvents);

    // Text label
    QLabel* lbl = new QLabel(label);
    lbl->setFont(segoe(10, active));
    lbl->setAttribute(Qt::WA_TransparentForMouseEvents);

    lay->addWidget(ico);
    lay->addWidget(lbl);
    lay->addStretch();

    if (active) {
        btn->setStyleSheet(
            "QPushButton { background:#EEF1FB; border-radius:8px; border:none; }"
            "QPushButton:hover { background:#DDE3F8; }");
        ico->setStyleSheet("color:#4d71a1;");
        lbl->setStyleSheet("color:#4d71a1; font-weight:bold;");
    } else {
        btn->setStyleSheet(
            "QPushButton { background:transparent; border-radius:8px; border:none; }"
            "QPushButton:hover { background:#EEF1FB; }");
        ico->setStyleSheet("color:#7B82A3;");
        lbl->setStyleSheet("color:#7B82A3;");
    }

    return btn;
}

// ══════════════════════════════════════════════════════════════
//  MAIN CONTENT
// ══════════════════════════════════════════════════════════════
QWidget* Homepage::buildMainContent()
{
    QWidget* content = new QWidget();
    content->setObjectName("mainContent");

    QVBoxLayout* lay = new QVBoxLayout(content);
    lay->setContentsMargins(32, 28, 32, 20);
    lay->setSpacing(0);

    // // Badge
    // QLabel* badge = new QLabel("ACADEMIC EXCELLENCE");
    // badge->setFont(segoe(8, true));
    // badge->setStyleSheet("color:#4d71a1; letter-spacing:1px;");
    // lay->addWidget(badge);
    // lay->addSpacing(8);

    // Welcome heading
    QLabel* welcome = new QLabel("Welcome");
    QLabel* Player = new QLabel("Player");
    Player->setStyleSheet("color:#3C6291; font-size: 32pt; font-weight:bold;");
    welcome->setStyleSheet("color:#1C1E2E; font-size: 32pt;");
    lay->addWidget(welcome);
    lay->addWidget(Player);
    lay->addSpacing(6);

    // Subtitle
    QLabel* subtitle = new QLabel(
        "Sharpen your mind and expand your vocabulary with today's\n"
        "hand-picked editorial challenges.");
    subtitle->setFont(segoe(10));
    subtitle->setStyleSheet("color:#7B82A3;");
    lay->addWidget(subtitle);
    lay->addSpacing(20);

    // Hero row: Start Game + Daily Quest
    QHBoxLayout* heroRow = new QHBoxLayout();
    heroRow->setSpacing(16);
    heroRow->addWidget(buildStartGameCard(), 2);
    heroRow->addWidget(buildDailyQuestCard(), 1);
    lay->addLayout(heroRow);
    lay->addSpacing(20);

    // Small cards row
    QHBoxLayout* cardRow = new QHBoxLayout();
    cardRow->setSpacing(16);
    cardRow->addWidget(buildSmallCard(ICO_BOOK,
                                      "Instructions",
                                      "Learn the rules of the quest and\nmaster advanced word finding."));
    cardRow->addWidget(buildSmallCard(ICO_INFO,
                                      "About",
                                      "Discover the story behind\nCrossWord Quest."));
    cardRow->addWidget(buildSmallCard(ICO_CLOSE,
                                      "Exit",
                                      "Safely close the application and\nsave your current progress."));
    lay->addLayout(cardRow);

    lay->addStretch();
    return content;
}

QWidget* Homepage::buildStartGameCard()
{
    QWidget* card = new QWidget();
    card->setObjectName("startCard");
    card->setMinimumHeight(165);
    card->setCursor(Qt::PointingHandCursor);

    QHBoxLayout* lay = new QHBoxLayout(card);
    lay->setContentsMargins(30, 30, 20, 30);
    lay->setSpacing(0);

    // Text
    QVBoxLayout* textCol = new QVBoxLayout();
    textCol->setSpacing(8);

    QLabel* title = new QLabel("Start Game");
    title->setFont(QFont("Segoe UI", 22, QFont::Bold));
    title->setStyleSheet("color:white;");

    QLabel* sub = new QLabel("Resume where you left off at Level 42");
    sub->setFont(segoe(10));
    sub->setStyleSheet("color:rgba(210,220,255,220);");

    textCol->addWidget(title);
    textCol->addWidget(sub);
    textCol->addStretch();

    lay->addLayout(textCol, 1);
    lay->addStretch();

    // Play button (owner-drawn circle with MDL2 play icon)
    PlayButton* play = new PlayButton(card);
    connect(play, &QPushButton::clicked, this, &Homepage::onStartGame);
    lay->addWidget(play);

    return card;
}

QWidget* Homepage::buildDailyQuestCard()
{
    QWidget* card = new QWidget();
    card->setObjectName("whiteCard");
    card->setMinimumHeight(165);

    QVBoxLayout* lay = new QVBoxLayout(card);
    lay->setContentsMargins(18, 16, 18, 16);
    lay->setSpacing(6);

    // Title row
    QHBoxLayout* titleRow = new QHBoxLayout();
    titleRow->setSpacing(10);

    QLabel* ico = new QLabel(QString::fromUtf8(ICO_CALENDAR));
    ico->setFont(mdl2(15));
    ico->setFixedSize(32, 32);
    ico->setAlignment(Qt::AlignCenter);
    ico->setStyleSheet("background:#EEF1FB; color:#4d71a1; border-radius:6px;");

    QLabel* title = new QLabel("Daily Quest");
    title->setFont(segoe(12, true));
    title->setStyleSheet("color:#1C1E2E;");

    titleRow->addWidget(ico);
    titleRow->addWidget(title);
    titleRow->addStretch();
    lay->addLayout(titleRow);

    QLabel* desc = new QLabel("A fresh puzzle every\nmorning.");
    desc->setFont(segoe(10));
    desc->setStyleSheet("color:#7B82A3;");
    lay->addWidget(desc);

    lay->addStretch();

    QPushButton* prog = new QPushButton("Check Progress  >");
    prog->setObjectName("progressBtn");
    prog->setCursor(Qt::PointingHandCursor);
    lay->addWidget(prog);

    return card;
}

QWidget* Homepage::buildSmallCard(const QString& icon,
                                  const QString& title,
                                  const QString& desc)
{
    QWidget* card = new QWidget();
    card->setObjectName("whiteCard");
    card->setMinimumHeight(110);
    card->setCursor(Qt::PointingHandCursor);

    QHBoxLayout* outer = new QHBoxLayout(card);
    outer->setContentsMargins(16, 14, 16, 14);
    outer->setSpacing(12);

    // Icon box
    QLabel* ico = new QLabel(QString::fromUtf8(icon.toUtf8()));
    ico->setFont(mdl2(14));
    ico->setFixedSize(36, 36);
    ico->setAlignment(Qt::AlignCenter);
    ico->setStyleSheet("background:#EEF1FB; color:#4d71a1; border-radius:8px;");

    // Text
    QVBoxLayout* textCol = new QVBoxLayout();
    textCol->setSpacing(4);

    QLabel* ttl = new QLabel(title);
    ttl->setFont(segoe(10, true));
    ttl->setStyleSheet("color:#1C1E2E;");

    QLabel* dsc = new QLabel(desc);
    dsc->setFont(segoe(9));
    dsc->setStyleSheet("color:#7B82A3;");
    dsc->setWordWrap(true);

    textCol->addWidget(ttl);
    textCol->addWidget(dsc);
    textCol->addStretch();

    outer->addWidget(ico, 0, Qt::AlignTop);
    outer->addLayout(textCol, 1);

    return card;
}

// ══════════════════════════════════════════════════════════════
//  BOTTOM STATS BAR
// ══════════════════════════════════════════════════════════════
QWidget* Homepage::buildBottomStats()
{
    QWidget* bar = new QWidget();
    bar->setObjectName("bottomBar");
    bar->setFixedHeight(72);

    QHBoxLayout* lay = new QHBoxLayout(bar);
    lay->setContentsMargins(60, 0, 60, 0);
    lay->setSpacing(0);

    auto addStat = [&](const QString& label,
                       const QString& value,
                       const QString& color)
    {
        QVBoxLayout* col = new QVBoxLayout();
        col->setSpacing(2);
        col->setAlignment(Qt::AlignVCenter);
        col->addWidget(makeStatLabel(label));
        col->addWidget(makeStatValue(value, color));
        lay->addStretch();
        lay->addLayout(col);
    };

    addStat("GLOBAL RANK",  "#1,204",  C_RANK_BLUE);
    addStat("WORDS SOLVED", "14.2k",   C_GREEN);
    addStat("WIN STREAK",   "12 Days", C_ORANGE);
    lay->addStretch();

    return bar;
}

QLabel* Homepage::makeStatLabel(const QString& text)
{
    QLabel* l = new QLabel(text);
    l->setFont(segoe(8, true));
    l->setStyleSheet(QString("color:%1; letter-spacing:0.5px;").arg(C_TEXT_MUTED));
    return l;
}

QLabel* Homepage::makeStatValue(const QString& text, const QString& color)
{
    QLabel* l = new QLabel(text);
    l->setFont(QFont("Segoe UI", 17, QFont::Bold));
    l->setStyleSheet(QString("color:%1;").arg(color));
    return l;
}

// ══════════════════════════════════════════════════════════════
//  SLOTS
// ══════════════════════════════════════════════════════════════
void Homepage::onStartGame()
{
    QMessageBox::information(this, "CrossWordQuest",
                             "Continuing at Level 42...");
}

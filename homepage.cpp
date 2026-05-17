#include "Homepage.h"

// ══════════════════════════════════════════════════════════════
//  Global stylesheet
// ══════════════════════════════════════════════════════════════
static const char* GLOBAL_QSS = R"(

    QWidget {
        font-family: 'Segoe UI';
        font-size: 12pt;
        color: #3C6291;
        background: transparent;
    }

    #topBar {
        background: #FFFFFF;
        border-bottom: 1px solid #E4E7F0;
    }

    #leftNav {
        background: #FFFFFF;
        border-right: 1px solid #E4E7F0;
    }

    #mainContent { background: #F8F9FC; }

    #whiteCard {
        background: #FFFFFF;
        border: 1px solid #3C6291;
        border-radius: 12px;
    }

    #startCard {
        background: qlineargradient(x1:0, y1:0, x2:1, y2:0,
                    stop:0 #3C6291, stop:1 #4D71A1);
        border-radius: 12px;
    }

    #chip {
        background: #F8F9FC;
        border: 1px solid #E4E7F0;
        border-radius: 14px;
    }

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

    QPushButton#navBtn {
        background: transparent;
        border: none;
        border-radius: 8px;
        color: #3C6291;
        font-size: 10pt;
        text-align: left;
        padding-left: 10px;
    }
    QPushButton#navBtn:hover { background: #EEF1FB; color: #4D71A1; }

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

    // Top bar (nav tabs + stats strip)
    root->addWidget(buildTopBar());

    // Middle: left nav + main content
    QHBoxLayout* middle = new QHBoxLayout();
    middle->setContentsMargins(0, 0, 0, 0);
    middle->setSpacing(0);
    middle->addWidget(buildLeftNav());
    middle->addWidget(buildMainContent(), 1);

    QWidget* middleWidget = new QWidget();
    middleWidget->setLayout(middle);
    middleWidget->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    root->addWidget(middleWidget, 1);

    // No bottom bar — stats are now in the top bar
}

// ══════════════════════════════════════════════════════════════
//  TOP BAR  (nav row + stats strip)
// ══════════════════════════════════════════════════════════════
QWidget* Homepage::buildTopBar()
{
    QWidget* bar = new QWidget();
    bar->setObjectName("topBar");

    QVBoxLayout* vlay = new QVBoxLayout(bar);
    vlay->setContentsMargins(0, 0, 0, 0);
    vlay->setSpacing(0);

    // ── Row 1: Nav tabs ──────────────────────────────────────
    QWidget* navRow = new QWidget();
    navRow->setFixedHeight(52);
    navRow->setStyleSheet("background:transparent;");

    QHBoxLayout* navLay = new QHBoxLayout(navRow);
    navLay->setContentsMargins(18, 0, 18, 0);
    navLay->setSpacing(4);

    QLabel* tabLevels = makeNavTab("Levels", true);
    navLay->addSpacing(20);
    navLay->addWidget(tabLevels);
    navLay->addStretch();

    // ── Row 2: Stats strip ───────────────────────────────────
    QWidget* statsRow = new QWidget();
    statsRow->setFixedHeight(48);
    statsRow->setStyleSheet(
        "background:#F0F4FA;"
        "border-top: 1px solid #E4E7F0;"
        "border-bottom: 1px solid #E4E7F0;");

    QHBoxLayout* statsLay = new QHBoxLayout(statsRow);
    statsLay->setContentsMargins(38, 0, 38, 0);
    statsLay->setSpacing(0);

    auto addStat = [&](const QString& label,
                       const QString& value,
                       const QString& color)
    {
        QWidget* cell = new QWidget();
        cell->setStyleSheet("background:transparent;");

        QHBoxLayout* cellLay = new QHBoxLayout(cell);
        cellLay->setContentsMargins(0, 0, 0, 0);
        cellLay->setSpacing(8);

        QLabel* lbl = new QLabel(label);
        lbl->setFont(segoe(8, true));
        lbl->setStyleSheet(QString("color:%1; letter-spacing:0.5px;"
                                   "background:transparent;").arg(C_TEXT_MUTED));

        QLabel* val = new QLabel(value);
        val->setFont(QFont("Segoe UI", 11, QFont::Bold));
        val->setStyleSheet(QString("color:%1; background:transparent;").arg(color));

        cellLay->addWidget(lbl);
        cellLay->addWidget(val);

        statsLay->addWidget(cell);
        statsLay->addStretch();
    };

    statsLay->addStretch();
    addStat("GLOBAL RANK",  "#1,204",  C_RANK_BLUE);
    addStat("WORDS SOLVED", "14.2k",   C_GREEN);
    addStat("WIN STREAK",   "12 Days", C_ORANGE);

    vlay->addWidget(navRow);
    vlay->addWidget(statsRow);

    return bar;
}

QLabel* Homepage::makeNavTab(const QString& text, bool active)
{
    QLabel* lbl = new QLabel(text);
    lbl->setFont(segoe(10, active));
    lbl->setAlignment(Qt::AlignCenter);
    lbl->setCursor(Qt::PointingHandCursor);
    lbl->setContentsMargins(14, 16, 14, 16);
    lbl->setStyleSheet(active
                           ? "color:#4D71A1; border-bottom:3px solid #4D71A1;"
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
    ico->setStyleSheet("color:#4D71A1;");

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

    QFrame* divider = new QFrame();
    divider->setFrameShape(QFrame::HLine);
    divider->setStyleSheet("color:#E4E7F0;");

    lay->addSpacing(8);
    lay->addWidget(divider);
    lay->addSpacing(6);

    lay->addWidget(makeNavBtn(ICO_HOME, "Home", true));

    lay->addStretch();

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

    QHBoxLayout* lay = new QHBoxLayout(btn);
    lay->setContentsMargins(10, 0, 10, 0);
    lay->setSpacing(8);

    QLabel* ico = new QLabel(QString::fromUtf8(icon.toUtf8()));
    ico->setFont(mdl2(13));
    ico->setFixedWidth(20);
    ico->setAlignment(Qt::AlignCenter);
    ico->setAttribute(Qt::WA_TransparentForMouseEvents);

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
        ico->setStyleSheet("color:#4D71A1;");
        lbl->setStyleSheet("color:#4D71A1; font-weight:bold;");
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

    // Welcome heading
    QLabel* welcome = new QLabel("Welcome");
    welcome->setStyleSheet("color:#1C1E2E; font-size:32pt;");

    QLabel* player = new QLabel("Player");
    player->setStyleSheet("color:#3C6291; font-size:32pt; font-weight:bold;");

    lay->addWidget(welcome);
    lay->addWidget(player);
    lay->addSpacing(6);

    // Subtitle
    QLabel* subtitle = new QLabel(
        "Sharpen your mind and expand your vocabulary with today's\n"
        "hand-picked editorial challenges.");
    subtitle->setStyleSheet("color:#7B82A3; font-size:10pt;");
    lay->addWidget(subtitle);
    lay->addSpacing(20);

    // Hero row: Start Game + Game Result
    QHBoxLayout* heroRow = new QHBoxLayout();
    heroRow->setSpacing(16);
    heroRow->addWidget(buildStartGameCard(), 2);
    heroRow->addWidget(buildGameResultCard(), 1);
    lay->addLayout(heroRow);
    lay->addSpacing(20);

    // Exit card only
    QHBoxLayout* cardRow = new QHBoxLayout();
    cardRow->setSpacing(8);
    cardRow->addWidget(buildSmallCard(ICO_CLOSE,
                                      "Exit",
                                      "Safely close the application and\nsave your current progress."));
    cardRow->addStretch();
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

    QVBoxLayout* textCol = new QVBoxLayout();
    textCol->setSpacing(8);

    QLabel* title = new QLabel("Start Game");
    title->setStyleSheet("color:white; font-size:22pt; font-weight:bold;");

    QLabel* sub = new QLabel("Resume where you left off at Level 42");
    sub->setStyleSheet("color:rgba(210,220,255,220); font-size:10pt;");

    textCol->addWidget(title);
    textCol->addWidget(sub);
    textCol->addStretch();

    lay->addLayout(textCol, 1);
    lay->addStretch();

    PlayButton* play = new PlayButton(card);
    connect(play, &QPushButton::clicked, this, &Homepage::onStartGame);
    lay->addWidget(play);

    return card;
}

QWidget* Homepage::buildGameResultCard()
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

    QLabel* ico = new QLabel(QString::fromUtf8(ICO_TROPHY));
    ico->setFont(mdl2(15));
    ico->setFixedSize(32, 32);
    ico->setAlignment(Qt::AlignCenter);
    ico->setStyleSheet("background:#EEF1FB; color:#4D71A1; border-radius:6px;");

    QLabel* title = new QLabel("Game Result");
    title->setStyleSheet("color:#1C1E2E; font-size:12pt; font-weight:bold;");

    titleRow->addWidget(ico);
    titleRow->addWidget(title);
    titleRow->addStretch();
    lay->addLayout(titleRow);

    QLabel* desc = new QLabel("Your last session\nresults are here.");
    desc->setStyleSheet("color:#7B82A3; font-size:10pt;");
    lay->addWidget(desc);

    lay->addStretch();

    QPushButton* btn = new QPushButton("View Results  >");
    btn->setObjectName("progressBtn");
    btn->setCursor(Qt::PointingHandCursor);
    lay->addWidget(btn);

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

    QLabel* ico = new QLabel(QString::fromUtf8(icon.toUtf8()));
    ico->setFont(mdl2(14));
    ico->setFixedSize(36, 36);
    ico->setAlignment(Qt::AlignCenter);
    ico->setStyleSheet("background:#EEF1FB; color:#4D71A1; border-radius:8px;");

    QVBoxLayout* textCol = new QVBoxLayout();
    textCol->setSpacing(4);

    QLabel* ttl = new QLabel(title);
    ttl->setStyleSheet("color:#1C1E2E; font-size:10pt; font-weight:bold;");

    QLabel* dsc = new QLabel(desc);
    dsc->setStyleSheet("color:#7B82A3; font-size:9pt;");
    dsc->setWordWrap(true);

    textCol->addWidget(ttl);
    textCol->addWidget(dsc);
    textCol->addStretch();

    outer->addWidget(ico, 0, Qt::AlignTop);
    outer->addLayout(textCol, 1);

    return card;
}

// ══════════════════════════════════════════════════════════════
//  SLOTS
// ══════════════════════════════════════════════════════════════
void Homepage::onStartGame()
{
    QMessageBox::information(this, "CrossWordQuest",
                             "Continuing at Level 42...");
}
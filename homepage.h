#pragma once

#include <QWidget>
#include <QLabel>
#include <QPushButton>
#include <QFrame>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QGridLayout>
#include <QPainter>
#include <QPainterPath>
#include <QFont>
#include <QColor>
#include <QSizePolicy>
#include <QSpacerItem>
#include <QMessageBox>
#include <QMouseEvent>

// ══════════════════════════════════════════════════════════════
//  Qt uses QSS (Qt Style Sheets) — like CSS — for all styling.
//  Icons use Segoe MDL2 Assets Unicode codepoints (Windows).
//  On Linux/Mac swap font to "Material Icons" or use QIcon.
// ══════════════════════════════════════════════════════════════

// Segoe MDL2 Assets codepoints
#define ICO_HOME      "\uE80F"
#define ICO_PUZZLE    "\uE7FC"
#define ICO_CALENDAR  "\uE787"
#define ICO_TROPHY    "\uE8D3"
#define ICO_SHOP      "\uE719"
#define ICO_HELP      "\uE897"
#define ICO_EXIT      "\uE7E8"
#define ICO_STAR      "\uE735"
#define ICO_CLOCK     "\uE823"
#define ICO_PLAY      "\uE768"
#define ICO_BOOK      "\uE82D"
#define ICO_INFO      "\uE946"
#define ICO_CLOSE     "\uE711"
#define ICO_GRID      "\uE8A9"

// ── Palette (as QSS hex strings) ─────────────────────────────
#define C_BRAND       "#3B5BDB"
#define C_BRAND_DK    "#1D3CB4"
#define C_BRAND_LIGHT "#EEF1FB"
#define C_BG          "#F8F9FC"
#define C_SURFACE     "#FFFFFF"
#define C_BORDER      "#E4E7F0"
#define C_TEXT_DARK   "#1C1E2E"
#define C_TEXT_MUTED  "#7B82A3"
#define C_GREEN       "#10B981"
#define C_ORANGE      "#F97316"
#define C_RANK_BLUE   "#1D4ED8"

// ── Reusable styled widgets ───────────────────────────────────

// Avatar circle — paints initials inside a filled circle
class AvatarWidget : public QWidget {
    Q_OBJECT
public:
    explicit AvatarWidget(QWidget* parent = nullptr) : QWidget(parent) {
        setFixedSize(34, 34);
        setCursor(Qt::PointingHandCursor);
    }
protected:
    void paintEvent(QPaintEvent*) override {
        QPainter p(this);
        p.setRenderHint(QPainter::Antialiasing);
        p.setBrush(QColor(C_BRAND));
        p.setPen(Qt::NoPen);
        p.drawEllipse(rect().adjusted(0,0,-1,-1));
        p.setPen(Qt::white);
        p.setFont(QFont("Segoe UI", 9, QFont::Bold));
        p.drawText(rect(), Qt::AlignCenter, "PS");
    }
};

// Play button — semi-transparent circle with MDL2 play glyph
class PlayButton : public QPushButton {
    Q_OBJECT
public:
    explicit PlayButton(QWidget* parent = nullptr) : QPushButton(parent) {
        setFixedSize(64, 64);
        setCursor(Qt::PointingHandCursor);
        setFlat(true);
        setAttribute(Qt::WA_TranslucentBackground);
    }
protected:
    void paintEvent(QPaintEvent*) override {
        QPainter p(this);
        p.setRenderHint(QPainter::Antialiasing);
        p.setBrush(QColor(255, 255, 255, 60));
        p.setPen(Qt::NoPen);
        p.drawEllipse(rect().adjusted(0,0,-1,-1));
        p.setPen(Qt::white);
        p.setFont(QFont("Segoe MDL2 Assets", 24));
        p.drawText(rect(), Qt::AlignCenter, QString::fromUtf8(ICO_PLAY));
    }
};

// ── Main Homepage widget ──────────────────────────────────────
class Homepage : public QWidget {
    Q_OBJECT

public:
    explicit Homepage(QWidget* parent = nullptr);

private:
    // Builder methods
    QWidget*     buildTopBar();
    QWidget*     buildLeftNav();
    QWidget*     buildMainContent();
    QWidget*     buildBottomStats();
    QWidget*     buildStartGameCard();
    QWidget*     buildDailyQuestCard();
    QWidget*     buildSmallCard(const QString& icon,
                                const QString& title,
                                const QString& desc);

    // Helpers
    QLabel*      makeNavTab(const QString& text, bool active);
    QWidget*     makeIconChip(const QString& icon, const QString& text);
    QPushButton* makeNavBtn(const QString& icon, const QString& label, bool active);
    QLabel*      makeStatLabel(const QString& text);
    QLabel*      makeStatValue(const QString& text, const QString& color);

    // Convenience font factories
    static QFont segoe(int pt, bool bold = false) {
        return QFont("Segoe UI", pt, bold ? QFont::Bold : QFont::Normal);
    }
    static QFont mdl2(int pt) {
        return QFont("Segoe MDL2 Assets", pt);
    }

private slots:
    void onStartGame();
};

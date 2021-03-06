#ifndef WIZDOCUMENTVIEW_H
#define WIZDOCUMENTVIEW_H

#include <QWidget>
#include <QWebView>
#include <QPointer>
#include <QTimer>

#include "wizdef.h"
#include "share/wizobject.h"
#include "share/wizsettings.h"

class CWizTitleBar;
class CWizDocumentWebView;
class CWizDatabase;
class CWizTagListWidget;
class CWizAttachmentListWidget;
class CWizNoteInfoForm;

class CWizDocumentView : public QWidget
{
    Q_OBJECT

public:
    CWizDocumentView(CWizExplorerApp& app, QWidget* parent = 0);
    virtual QSize sizeHint() const { return QSize(200, 1); }

    CWizDocumentWebView* web() const { return m_web; }
    QWidget* client() const { return m_client; }

private:
    CWizExplorerApp& m_app;
    CWizUserSettings& m_userSettings;

protected:
    CWizDatabaseManager& m_dbMgr;
    QPointer<CWizTitleBar> m_title;
    CWizDocumentWebView* m_web;
    QWidget* m_client;
    QPointer<CWizTagListWidget> m_tags;
    QPointer<CWizAttachmentListWidget> m_attachments;
    QPointer<CWizNoteInfoForm> m_info;

    QWidget* createClient();

    bool m_editingDocument;
    WizDocumentViewMode m_viewMode;

    QTimer m_timerDelay;
    WIZDOCUMENTDATA m_dataDelay;

public:
    bool viewDocument(const WIZDOCUMENTDATA& data, bool forceEdit);
    void setReadOnly(bool b, bool isGroup);
    void showClient(bool visible);
    const WIZDOCUMENTDATA& document();
    void editDocument(bool editing);
    bool isEditingDocument() const { return m_editingDocument; }
    void setViewMode(WizDocumentViewMode mode);
    void setModified(bool modified);
    void settingsChanged();

public Q_SLOTS:
    void on_titleEdit_textChanged(const QString& strTitle);
    void on_titleEdit_textEdit_writeDelay();
    void on_editDocumentButton_clicked();
    void on_tagsButton_clicked();
    void on_attachmentButton_clicked();
    void on_infoButton_clicked();
    void on_attachment_created(const WIZDOCUMENTATTACHMENTDATA& attachment);
    void on_attachment_deleted(const WIZDOCUMENTATTACHMENTDATA& attachment);
    void on_document_modified(const WIZDOCUMENTDATA& documentOld, const WIZDOCUMENTDATA& documentNew);

};

#endif // WIZDOCUMENTVIEW_H

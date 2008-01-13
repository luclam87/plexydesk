#ifndef PLEXY_DESKTOP_WIDGET_H
#define PLEXY_DESKTOP_WIDGET_H	
#include <plexy.h>
#include <QtCore>
#include <QtGui>

namespace PlexyDesk
{
	class DesktopWidget:public QObject, public QGraphicsRectItem
	{
		Q_OBJECT
	public:
		typedef enum {	DOCK,
				NORMALSIDE,
				BACKSIDE} State;

		DesktopWidget(const QRectF &rect, QWidget *embeddedWidget = 0);

		virtual ~DesktopWidget();

		virtual void paintBackSide (QPainter * painter,const QRectF& rect);
		virtual void paintViewSide (QPainter * painter,const QRectF& rect);
		virtual void paintDockView (QPainter * painter,const QRectF& rect); 
		virtual void setState(State s);
		virtual QRectF boundingRect() const;
		virtual void hoverEnterEvent(QGraphicsSceneHoverEvent *event);
	
	public slots:
				void updateStep(qreal);
				void stateChanged(QTimeLine::State);
				void animate();
				
	protected:
		virtual void paint(QPainter * painter, const QStyleOptionGraphicsItem * option, QWidget * widget = 0); 
		virtual void mouseReleaseEvent ( QGraphicsSceneMouseEvent * event );
	private:
		class Private ;
		Private * const d;

	
	};
}//

#endif

#include "ForceDirectedLayout.h"
#include <QtMath>
#include <cmath>
#include <random>

void ForceDirectedLayout::applyLayout(const QList<FSMState *> &states, const QList<FSMTransition *> &transitions, int width, int height, int iterations)
{
    const double area = width * height;
    const double k = qSqrt(area / states.size());
    double temperature = 50.0;

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<double> xDist(0.0, width);
    std::uniform_real_distribution<double> yDist(0.0, height);

    QMap<FSMState *, QPointF> displacements;
    for (FSMState *v : states)
    {
        QPointF initialPos(xDist(gen), yDist(gen));
        v->setPos(initialPos);
    }

    for (int i = 0; i < iterations; ++i)
    {
        // Reset displacements
        for (FSMState *v : states)
        {
            displacements[v] = QPointF(0, 0);
        }

        // Repulsive forces
        for (FSMState *v : states)
        {
            for (FSMState *u : states)
            {
                if (v == u)
                    continue;
                QPointF delta = v->pos() - u->pos();
                double dist = std::max(0.01, std::hypot(delta.x(), delta.y()));
                QPointF repulse = delta / dist * (k * k / dist);
                displacements[v] += repulse;
            }
        }

        // Attractive forces
        for (FSMTransition *t : transitions)
        {
            FSMState *v = t->getFirstState();
            FSMState *u = t->getSecondState();
            if (!v || !u || v == u)
                continue;

            QPointF delta = v->pos() - u->pos();
            double dist = std::max(0.01, std::hypot(delta.x(), delta.y()));
            QPointF attract = delta / dist * (dist * dist / k);
            displacements[v] -= attract;
            displacements[u] += attract;
        }

        // Limit max displacement and update positions
        for (FSMState *v : states)
        {
            QPointF disp = displacements[v];
            double dist = std::hypot(disp.x(), disp.y());
            if (dist > 0)
            {
                QPointF limitedDisp = disp / dist * std::min(dist, temperature);
                QPointF newPos = v->pos() + limitedDisp;

                // clamp to scene size
                newPos.setX(std::clamp(newPos.x(), 0.0, static_cast<double>(width)));
                newPos.setY(std::clamp(newPos.y(), 0.0, static_cast<double>(height)));

                v->setPos(newPos);
            }
        }

        // Cooling temperature
        temperature *= 0.95;
    }
}
//     ____  __________ ___   ____ ___  ___
//    / __ \/ ____/ __ \__ \ / __ \__ \|__ \
//   / /_/ / /   / / / /_/ // / / /_/ /__/ /
//  / ____/ /___/ /_/ / __// /_/ / __// __/
// /_/    \____/\____/____/\____/____/____/
//
// Rien à modifier ici

#ifndef LAUNCHABLE_H
#define LAUNCHABLE_H

#include <QDebug>

#include <pcosynchro/pcothread.h>

/*!
 * \brief La classe Launchable est une classe abstraite qui représente le fait d'avoir un thread
 * associé qui permet d'être lancé, thread qui exécute la fonction run() qui représente le
 * comportement de la classe qui la définit.
 */
class Launchable
{
public:
    Launchable() {}

    /*!
     * \brief startThread Lance un thread avec la fonction run()
     */
    void startThread() {
        if (thread == nullptr) {
            printStartMessage();
            thread = std::make_unique<PcoThread>(&Launchable::run, this);
        }
    }

    /*!
     * \brief join Attend la fin du thread lancé
     */
    void join() {
        if (thread != nullptr) {
            thread->join();
            printCompletionMessage();
        }
    };

protected:

    /*!
     * \brief run La fonction à lancer, ici abstraite (virtuelle pure), est redéfinie par les
     * classes concrètes qui héritent de la classe Launchable.
     */
    virtual void run() = 0;

    /*!
     * \brief printStartMessage Message affiché au lancement du thread
     */
    virtual void printStartMessage() {qDebug() << "[START] Un thread lancé";}

    /*!
     * \brief printCompletionMessage Message affiché après la fin du thread
     */
    virtual void printCompletionMessage() {qDebug() << "[STOP] Un thread a terminé";}

    /*!
     * \brief thread Le thread associé
     */
    std::unique_ptr<PcoThread> thread = nullptr;

};

#endif // LAUNCHABLE_H

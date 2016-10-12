#include "Solver.h"

unsigned long Solver::Node::N = 1;

Solver::Solver(unsigned long N)
    :root(NULL)
{
    if(N <= 0)
        std::cout << " This is a bad game" << std::endl;
    this->N = N;
}

Solver::~Solver()
{
    if(root)
        delete root;
}

Triplet Solver::solve()
{
    //clock_t start = clock();

    DATA* d= new DATA(N);
    for(size_t i = 0 ; i < N ; ++i)
        (*d)[i] = true;
    root = new Node(d);
    root->heuristic_coeff = N;

    Node::N = N;
    Triplet result;
    //clock_t finish = clock();
    //std::cout << "Time to init :" << (finish - start)* 0.01 << std::endl;
    generate(root);
    //start = clock();
    //std::cout << "Time to generate tree: " << (start - finish)* 0.01 << std::endl;
    //result.third = mM(root, Player::MAX, 0, INT_MIN, INT_MAX);
    miniMaxStarter(result.first, result.second, result.third);

    //finish = clock();
    //std::cout << "Time to calculate :" << (finish - start) << std::endl;

    return result;
}

void Solver::miniMaxStarter(int& pos, int& amount, int& points)
{
    pos = 0;
    amount = 0;
    points = 0;
    if(this->N <= 0)
        return;

    int best_moves_lt = 0;
    Node* best_lt = NULL;
    int best_moves_gt = INT_MAX;
    Node* best_gt = NULL;
    int current_moves;

    int alpha = INT_MIN;
    int beta = INT_MAX;
    //std::sort(current->children.begin(), current->children.end(), [](Node* f, Node* l){return f->heuristic_coeff < l->heuristic_coeff;});
    size_t len = root->children.size();
    for(size_t i = 0 ; i < len; ++i)
    {
        current_moves = mM(root->children[i], Player::MIN, 1, alpha, beta);
        if(current_moves > 0)
        {
            if(best_moves_gt > current_moves)
            {
                best_moves_gt = current_moves;
                best_gt = root->children[i];
            }
        }
        else
        {
            if(best_moves_lt > current_moves)
            {
                best_moves_lt = current_moves;
                best_lt = root->children[i];
            }
        }
        if(best_moves_gt < INT_MAX && alpha < best_moves_gt)
            alpha = best_moves_gt;
        else if(alpha > best_moves_lt)
            alpha = best_moves_lt;
        if(alpha > beta)
            break;
    }

    if(best_moves_gt < INT_MAX)
    {
        size_t i = 0;
        if((*best_gt->data)[0] == true || (*best_gt->data)[this->N-1] == true)
        {
            for(; i < this->N; ++i)
            {
                if((*best_gt->data)[i] == false)
                    break;
            }
        }
        else
        {
            i = this->N - 2;
            if((*best_gt->data)[i] == true)
                ++i;
        }
        pos = i;
        amount = this->N - best_gt->heuristic_coeff;
        points = best_moves_gt;
    }
    else
    {
        size_t i = 0;
        if((*best_lt->data)[0] == true || (*best_lt->data)[this->N-1] == true)
        {
            for(; i < this->N; ++i)
            {
                if((*best_lt->data)[i] == false)
                    break;
            }
        }
        else
        {
            i = this->N - 2;
            if((*best_gt->data)[i] == true)
                ++i;
        }
        pos = i;
        amount = this->N - best_lt->heuristic_coeff;
        points = best_moves_lt;
    }
    if(points < 0)
        points = -N - points;
    else
        points = N - points;
}
int Solver::mM(Node* current , Player atTurn, size_t moves, int alpha, int beta)
{
    //std::cout << "Entering with " ;
    //current->print();
    //std::cout << " children size " << current->children.size() << " moves " << moves << std::endl;
    if(current->children.size() == 0)
        return moves * ((atTurn == Player::MAX) ? -1 : 1 );

    if(atTurn == Player::MAX)
    {
        int best_moves_lt = 0;
        int best_moves_gt = INT_MAX;
        int current_moves;
        //std::sort(current->children.begin(), current->children.end(), [](Node* f, Node* l){return f->heuristic_coeff < l->heuristic_coeff;});
        for(size_t i = 0 ; i < current->children.size(); ++i)
        {
            current_moves = mM(current->children[i], Player::MIN, moves + 1, alpha, beta);
            if(current_moves > 0)
            {
                if(best_moves_gt > current_moves)
                    best_moves_gt = current_moves;
            }
            else
            {
                if(best_moves_lt > current_moves)
                    best_moves_lt = current_moves;
            }
            if(best_moves_gt < INT_MAX && alpha < best_moves_gt)
                alpha = best_moves_gt;
            else if(alpha > best_moves_lt)
                alpha = best_moves_lt;
            if(alpha > beta)
                break;
        }
        if(best_moves_gt < INT_MAX)
            return best_moves_gt;
        else
            return best_moves_lt;
    }
    else
    {
        int best_moves_lt = INT_MIN;
        int best_moves_gt = 0;
        int current_moves;
        //std::sort(current->children.begin(), current->children.end(), [](Node* f, Node* l){return f->heuristic_coeff > l->heuristic_coeff;});
        for(size_t i = 0 ; i < current->children.size(); ++i)
        {
            current_moves = mM(current->children[i], Player::MAX, moves + 1, alpha, beta);
            if(current_moves < 0)
            {
                if(best_moves_lt < current_moves)
                    best_moves_lt = current_moves;
            }
            else
            {
                if(best_moves_gt < current_moves)
                    best_moves_gt = current_moves;
            }
            if(best_moves_lt > INT_MIN && beta > best_moves_lt)
                beta = best_moves_lt;
            else if(beta < best_moves_gt)
                beta = best_moves_gt;
            if(alpha > beta)
                break;
        }
        if(best_moves_lt > INT_MIN)
            return best_moves_lt;
        else
            return best_moves_gt;
    }
}
void Solver::print()
{
    print(root, 0);
}
void Solver::generate(Node* current)
{
    current->generate_children();

    for(size_t i = 0; i < current->children.size(); ++i)
        generate(current->children[i]);
}
void Solver::print(Node* current, size_t offset)
{
    std::cout << std::setw(offset) << ' ';
    current->print();
    for(size_t i = 0; i < current->children.size(); ++i)
    {
        std::cout << std::endl;
        print(current->children[i], offset + 3);
    }
}

void Solver::Node::generate_children()
{
    DATA* toADD;
    Node* temp;

    // in order not to generate the nodes after we have a certain winable position
    if(this->heuristic_coeff == 0)
        return;
    if(this->heuristic_coeff <= 3)
    {
        bool go_on = true;
        size_t i = 0;
        while(i < this->N)
        {
            if((*this->data)[i] == true)
            {
                if((*this->data)[i+1] == false || (*this->data)[i+2] == false)
                    go_on = false;
                break;
            }
            ++i;
        }
        if(go_on)
        {
            toADD = new DATA(this->N);
            for(size_t i = 0; i < this->N; ++i)
                (*toADD)[i] = false;
            temp = new Node(toADD);
            temp->heuristic_coeff = 0;
            this->children.push_back(temp);
            return;
        }
    }
    for(size_t i = 0 ; i < N; ++i)
    {
        if((*data)[i])
        {
            (*data)[i] = false;
            toADD = new DATA(*data);
            temp = new Node(toADD);
            temp->heuristic_coeff = this->heuristic_coeff - 1;
            //temp->heuristic();
            children.push_back(temp);

            if((*data)[(i + 1)%N])
            {
                (*data)[(i + 1)%N] = false;
                toADD = new DATA(*data);
                temp = new Node(toADD);
                temp->heuristic_coeff = this->heuristic_coeff - 2;
                //temp->heuristic();
                children.push_back(temp);

                if((*data)[(i + 2)%N])
                {
                    (*data)[(i + 2)%N] = false;
                    toADD = new DATA(*data);
                    temp = new Node(toADD);
                    temp->heuristic_coeff = this->heuristic_coeff - 3;
                    //temp->heuristic();
                    children.push_back(temp);
                    (*data)[(i + 2)%N] = true;
                }
                (*data)[(i + 1)%N] = true;
            }
            (*data)[i] = true;
        }
    }
}

void Solver::Node::print() const
{
    for(size_t i = 0 ; i < N; i++)
    {
        if((*data)[i])  std::cout << '1';
        else            std::cout << '0';
    }
}

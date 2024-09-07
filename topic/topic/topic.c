#include"topic.h"

bool IsHits(p_FirstQuestion pVal1, p_coordinates pVal2)
{
    return (fabs(pVal2->_x) <= pVal1->submarine->_length / 2) && (fabs(pVal2->_y) <= pVal1->submarine->_width / 2);
}

double HitRate(p_FirstQuestion pVal1, p_coordinates pVal2)
{
    double depth_submarine_top = pVal1->bombshell->_detonation_depth + pVal1->submarine->_height / 2;
    double depth_submarine_bottom = pVal1->bombshell->_detonation_depth - pVal1->submarine->_height / 2;
    double prob_horizontal = gsl_ran_gaussian_pdf(pVal2->_x, pVal1->sigma) * gsl_ran_gaussian_pdf(pVal2->_y, pVal1->sigma);
    double prob_depth_upper = gsl_cdf_gaussian_P(depth_submarine_top - pVal1->bombshell->_detonation_depth, 0.0001);
    double prob_depth_lower = gsl_cdf_gaussian_P(depth_submarine_bottom - pVal1->bombshell->_detonation_depth, 0.0001);
    double total_hit_probability = prob_horizontal * (prob_depth_upper + (1 - prob_depth_lower));
    return total_hit_probability;
}

double* linspace(double start, double stop, int size)
{
    double* ret = (double*)malloc(sizeof(double) * size);
    if (ret == NULL)
    {
        perror("linspace malloc fail");
        return NULL;
    }
    double pacemaker = (stop - start) / (size - 1);
    double current = start;
    int i = 0;
    for (; i < size; i++)
    {
        ret[i] = current;
        current += pacemaker;
    }
    return ret;
}

p_FirstQuestion topicInit(void)
{
    p_SubmarineSpecifications p1 = (p_SubmarineSpecifications)malloc(sizeof(SubmarineSpecifications));
    if (p1 == NULL)
    {
        perror("topicInit malloc Submarine fail");
        return NULL;
    }
    p1->_height = 25.0;
    p1->_length = 100.0;
    p1->_width = 20.0;
    p_BombRelatedInformation p2 = (p_BombRelatedInformation)malloc(sizeof(BombRelatedInformation));
    if (p2 == NULL)
    {
        free(p1);
        perror("topicInit malloc bombshell fail");
        return NULL;
    }
    p2->_kill_radius = 20.0;
    p2->_detonation_depth = 150;
    p_FirstQuestion p3 = (p_FirstQuestion)malloc(sizeof(FirstQuestion));
    if (p3 == NULL)
    {
        free(p1);
        free(p2);
        perror("topicInit fail");
        return NULL;
    }
    p3->submarine = p1;
    p3->bombshell = p2;
    p3->sigma = 120.0;
    return p3;
}

void prescription(void)
{
    p_FirstQuestion p = topicInit();
    double* p_bomb_x_range = linspace(0, p->submarine->_length, p->submarine->_width);
    double* p_bomb_y_range = linspace(0, p->submarine->_height, p->submarine->_height);
    double* depth_setting = linspace(0, p->bombshell->_detonation_depth, p->bombshell->_detonation_depth);
    double max_probability = 0;
    coordinates cot = { 0 };
    coordinates ret = { 0 };
    int i, j, k;
    for (i = 0; i < p->submarine->_width; i++)
    {
        for (j = 0; j < p->submarine->_height; j++)
        {
            for (k = 0; k < p->bombshell->_detonation_depth; k++)
            {
                cot._x = p_bomb_x_range[i];
                cot._y = p_bomb_y_range[j];
                cot._z = depth_setting[k];
                double temp = HitRate(p, &cot);
                if (temp > max_probability)
                {
                    max_probability = temp;
                    ret._x = cot._x;
                    ret._y = cot._y;
                    ret._y = cot._y;
                }
            }
        }
    }
    printf("最大命中概率为%f\n", max_probability);
    printf("最佳投弹落点为{ %f, %f }\n", ret._x, ret._y);
    printf("最佳引信引爆深度为%f\n", ret._y);
}

int main()
{
    prescription();
    return 0; 
}
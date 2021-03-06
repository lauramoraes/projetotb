<?xml version="1.0" encoding="ISO-8859-1"?>

<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version="1.0">


<!-- Crit�rio inicial de triagem para TB pulmonar -->

<xsl:template match="triagem">
			<tr>
				<td class="title1" width="50%">N�mero Geral:</td>
				<td class="answer1" width="50%"><xsl:value-of select="numeroGeral" /></td>
			</tr>
			<tr>
				<td class="title2">Nome:</td>
				<td class="answer2"><xsl:value-of select="nomeCompleto" /></td>
			</tr>
			<tr>
				<td class="title1">Nome da m�e:</td>
				<td class="answer1"><xsl:value-of select="nomeMae" /></td>
			</tr>
			<tr>
				<td class="title2">Endere�o residencial:</td>
				<td class="answer2"><xsl:value-of select="endereco" /></td>
			</tr>
			<tr>
				<td class="title2">Ponto de Refer�ncia:</td>
				<td class="answer2"><xsl:value-of select="ptoReferencia" /></td>
			</tr>
			<tr>
				<td class="title2">Bairro:</td>
				<td class="answer2"><xsl:value-of select="bairro" /></td>
			</tr>
			<tr>
				<td class="title2">Cidade:</td>
				<td class="answer2"><xsl:value-of select="cidade" /></td>
			</tr>
			<tr>
				<td class="title2">CEP:</td>
				<td class="answer2"><xsl:value-of select="concat(cep1, '-', cep2)" /></td>
			</tr>
			<tr>
				<td class="title2">Telefone:</td>
				<td class="answer2"><xsl:value-of select="fone" /></td>
			</tr>
			<tr>
				<td class="title1">Celular:</td>
				<td class="answer1"><xsl:value-of select="cel" /></td>
			</tr>
			<tr>
				<td class="title2">Contato para emerg�ncia:</td>
				<td class="answer2"><xsl:value-of select="concat(foneContato,' - ', nomeContato)" /></td>
			</tr>
			<tr>
				<td class="title1">Data de Nascimento:</td>
				<td class="answer1"><xsl:value-of select="dia_nascimento" />/<xsl:value-of select="mes_nascimento" />/<xsl:value-of select="ano_nascimento" /></td>
			</tr>
			<tr>
				<td class="title2">Idade:</td>
				<td class="answer2"><xsl:value-of select="concat(idade, ' ', idade/@unidade)" /></td>
			</tr>
			<tr>
				<td class="title1">Naturalidade:</td>
				<td class="answer1"><xsl:value-of select="concat(naturalidadeCidade,' - ',naturalidadeEstado)" /></td>
			</tr>
			<xsl:if test="naturalidadeAnosRio">
				<tr>
					<td class="title1">Chegou no Rio h� quantos anos?</td>
					<td class="answer1"><xsl:value-of select="naturalidadeAnosRio" /></td>
				</tr>
			</xsl:if>
			<tr>
				<td class="title2">Sexo:</td>
				<td class="answer2"><xsl:value-of select="sexo" /></td>
			</tr>
			<tr>
				<td class="title1">Ra�a-I:</td>
				<td class="answer1"><xsl:value-of select="raca1" /></td>
			</tr>
			<xsl:if test="raca1[. != 'branco']">
				<tr>
					<td class="title1">Especifica��o:</td>
					<td class="answer1"><xsl:value-of select="raca2" /></td>
				</tr>
			</xsl:if>
			<tr>
				<td class="title2">Estado Civil:</td>
				<td class="answer2"><xsl:value-of select="estadoCivil" /></td>
			</tr>
			<tr>
				<td class="title1">Tem companheiro(a)?</td>
				<td class="answer1"><xsl:value-of select="companheiro" /></td>
			</tr>
			<tr>
				<td class="title2">Peso habitual:</td>
				<td class="answer2"><xsl:value-of select="concat(pesoHabitual,' ',pesoHabitual/@unidade)" /></td>
			</tr>
			<tr>
				<td class="title1">Peso atual:</td>
				<td class="answer1"><xsl:value-of select="concat(pesoAtual,' ',pesoAtual/@unidade)" /></td>
			</tr>
			<tr>
				<td class="title1">Perda de peso (&gt; 10%):</td>
				<td class="answer1"><xsl:value-of select="perdaDePeso" /></td>
			</tr>
			<xsl:if test="perdaDePeso_semanas">
				<tr>
					<td class="title1">Semanas com perda de peso &gt;10%:</td>
					<td class="answer1"><xsl:value-of select="perdaDePeso_semanas" /></td>
				</tr>
			</xsl:if>
			<tr>
				<td class="title2">Altura:</td>
				<td class="answer2"><xsl:value-of select="concat(altura, ' ', altura/@unidade)" /></td>
			</tr>
			<tr>
				<td class="title1">IMC:</td>
				<td class="answer1"><xsl:value-of select="imc" /></td>
			</tr>
			
			
			<tr>
				<td class="title4" colspan="2">Sinais e Sintomas</td>
			</tr>
			
			
			<tr>
				<td class="title1">Tosse:</td>
				<td class="answer1"><xsl:value-of select="tosse" />
					<xsl:if test="(tosse != 'nao') and (tosse_semanas != '')">
						<xsl:value-of select="concat('. ',tosse_semanas,' semanas')" />
					</xsl:if>
				</td>
			</tr>
			<tr>
				<td class="title2">Expectora��o:</td>
				<td class="answer2"><xsl:value-of select="expectoracao" />
					<xsl:if test="(expectoracao != 'nao') and (expectoracao_semanas != '')">
						<xsl:value-of select="concat('. ',expectoracao_semanas,' semanas')" />
					</xsl:if>
				</td>
				
			</tr>
			<tr>
				<td class="title1">Hemopt�ico:</td>
				<td class="answer1"><xsl:value-of select="hemoptoico" />
					<xsl:if test="(hemoptoico != 'nao') and (hemoptoico_semanas != '')">
						<xsl:value-of select="concat('. ',hemoptoico_semanas,' semanas')" />
					</xsl:if>
				</td>
			</tr>
			<tr>
				<td class="title2">Hemoptise:</td>
				<td class="answer2"><xsl:value-of select="hemoptise" />
					<xsl:if test="(hemoptise != 'nao') and (hemoptise_semanas != '')">
						<xsl:value-of select="concat('. ',hemoptise_semanas,' semanas')" />
					</xsl:if>
				
				</td>
			</tr>
			<xsl:if test="hemoptise[. = 'sim']">
				<tr>
					<td class="title2">Quantidade:</td>
					<td class="answer2"><xsl:value-of select="hemoptiseQtd" /></td>
				</tr>
			</xsl:if>
			<tr>
				<td class="title1">Sudorese noturna:</td>
				<td class="answer1"><xsl:value-of select="sudorese" />
					<xsl:if test="(sudorese != 'nao') and (sudorese_semanas != '')">
						<xsl:value-of select="concat('. ',sudorese_semanas,' semanas')" />
					</xsl:if>
				</td>
			</tr>
			<tr>
				<td class="title2">Febre:</td>
				<td class="answer2"><xsl:value-of select="febre" />
					<xsl:if test="(febre != 'nao') and (febre_semanas != '')">
						<xsl:value-of select="concat('. ',febre_semanas,' semanas')" />
					</xsl:if>
				</td>
			</tr>
			<tr>
				<td class="title1">Dispn�ia:</td>
				<td class="answer1"><xsl:value-of select="dispneia" />
					<xsl:if test="(dispneia != 'nao') and (dispneia_semanas != '')">
						<xsl:value-of select="concat('. ',dispneia_semanas,' semanas')" />
					</xsl:if>
				</td>
			</tr>
			<tr>
				<td class="title2">Perda do apetite:</td>
				<td class="answer2"><xsl:value-of select="perdaApetite" />
					<xsl:if test="(perdaApetite != 'nao') and (perdaApetite_semanas != '')">
						<xsl:value-of select="concat('. ',perdaApetite_semanas,' semanas')" />
					</xsl:if>
				</td>
			</tr>
			<tr>
				<td class="title2">Dor tor�cica</td>
				<td class="answer2"><xsl:value-of select="dorToracica" />
					<xsl:if test="(dorToracica != 'nao') and (dorToracica_semanas != '')">
						<xsl:value-of select="concat('. ',dorToracica_semanas,' semanas')" />
					</xsl:if>
				</td>
			</tr>
			<tr>
				<td class="title1">Total de pontos:</td>
				<td class="answer1"><xsl:value-of select="pontuacao" /></td>
			</tr>
			
			
			<tr>
				<td class="title4" colspan="2">Hist�ria da Tuberculose</td>
			</tr>
			
			
			<tr>
				<td class="title1">Tratamento anterior para TB:</td>
				<td class="answer1"><xsl:value-of select="tratamentoAnteriorTB" /></td>
			</tr>
			<xsl:if test="tratamentoAnteriorTB[. = 'sim']">
				<tr>
					<td class="title1">Data de diagn�stico de TB no passado:</td>
					<td class="answer1"><xsl:value-of select="concat(mes_diagnostico,'/',ano_diagnostico)" /></td>
				</tr>
				<tr>
					<td class="title1">TB desfecho:</td>
					<td class="answer1"><xsl:value-of select="TBdesfecho" /></td>
				</tr>
			</xsl:if>
			<tr>
				<td class="title2">Esteve internado em hospital?</td>
				<td class="answer2"><xsl:value-of select="internado" /></td>
			</tr>
			<tr>
				<td class="title1">Esteve em pris�o?</td>
				<td class="answer1"><xsl:value-of select="prisao" /></td>
			</tr>
			<tr>
				<td class="title2">Esteve em delegacia?</td>
				<td class="answer2"><xsl:value-of select="delegacia" /></td>
			</tr>
			<tr>
				<td class="title1">Teve contato com pessoa com TBP?</td>
				<td class="answer1"><xsl:value-of select="contatoTBP" /></td>
			</tr>
			<xsl:if test="contatoTBP[. = 'sim']">
				<tr>
					<td class="title1">Morava junto?</td>
					<td class="answer1"><xsl:value-of select="contatoTBPmoravaJunto" /></td>
				</tr>
				<tr>
					<td class="title1">Trabalhava junto?</td>
					<td class="answer1"><xsl:value-of select="contatoTBPtrabalhavaJunto" /></td>
				</tr>
				<tr>
					<td class="title1">Era amigo, parente ou colega que n�o morava junto?</td>
					<td class="answer1"><xsl:value-of select="contatoTBPamigoParenteColega" /></td>
				</tr>
				<tr>
					<td class="title1">Algum destes contatos foi &lt; 3 anos?</td>
					<td class="answer1"><xsl:value-of select="contatoTBPmenorQue3Anos" /></td>
				</tr>
				<tr>
					<td class="title1">Qual?</td>
					<td class="answer1">
						<xsl:for-each select="contatoTBPqual">
							<xsl:value-of select="." />. 
						</xsl:for-each>
					</td>
				</tr>
			</xsl:if>
			<tr>
				<td class="title2">Fuma?</td>
				<td class="answer2"><xsl:value-of select="fuma" /></td>
			</tr>
			<xsl:if test="fuma[. != 'nunca']">
				<tr>
					<td class="title2">N�mero de cigarros que fuma ou fumava por dia:</td>
					<td class="answer2"><xsl:value-of select="fumaQtd" /></td>
				</tr>
				<tr>
					<td class="title2">N�mero de anos que fuma ou fumou:</td>
					<td class="answer2"><xsl:value-of select="fumaTempo" /></td>
				</tr>
			</xsl:if>
			<tr>
				<td class="title1 wrap">Antes de ficar doente tomava alguma bebida alco�lica? Qual tipo de bebida prefere ou preferia?</td>
				<td class="answer1">
					<xsl:for-each select="bebida"><xsl:value-of select="." />. </xsl:for-each>
					<!--<xsl:value-of select="bebida" />-->
				</td>
			</tr>
			<xsl:if test="bebida[. != 'nenhuma']">
				<tr>
					<td class="title1">Tem facilidade de fazer amizades?</td>
					<td class="answer1"><xsl:value-of select="facilidadeFazerAmizades" /></td>
				</tr>
				<tr>
					<td class="title1">Alguma vez sentiu que deveria diminuir a quantidade da bebida?</td>
					<td class="answer1"><xsl:value-of select="diminuirQtdBebida" /></td>
				</tr>
				<tr>
					<td class="title1">Algu�m critica ou j� criticou seu modo de beber?</td>
					<td class="answer1"><xsl:value-of select="criticaModoBeber" /></td>
				</tr>
				<tr>
					<td class="title1">Costuma beber de manh� para diminuir o nervosismo/ressaca?</td>
					<td class="answer1"><xsl:value-of select="bebidaManha" /></td>
				</tr>
				<tr>
					<td class="title1">Sente-se culpado pela maneira que costuma beber?</td>
					<td class="answer1"><xsl:value-of select="culpadoManeiraBeber" /></td>
				</tr>
			</xsl:if>
			<tr>
				<td class="title2">Cage:</td>
				<td class="answer2"><xsl:value-of select="cage" /></td>
			</tr>
			
<!-- Perguntas finais de enfermagem -->
			<tr>
				<td class="title4" colspan="2">Perguntas Finais de Enfermagem</td>
			</tr>
			
			
			<tr>
				<td class="title1">Primeira vez que procurou aux�lio:</td>
				<td class="answer1"><xsl:value-of select="primeiraProcuraParaAuxiliodeSaude" /></td>
			</tr>
			<tr>
				<td class="title1">Local:</td>
				<td class="answer1"><xsl:value-of select="lugarDaPrimeiraConsulta" /></td>
			</tr>
			<tr>
				<td class="title1">Causa:</td>
				<td class="answer1"><xsl:value-of select="causaDaPrimeiraConsulta" /></td>
			</tr>
			<tr>
				<td class="title1">Acompanhado de familiares?</td>
				<td class="answer1"><xsl:value-of select="veioAcompanhadoDeFamiliares" /></td>
			</tr>
			<tr>
				<td class="title1">Encaminhado pelo P. de Sa�de Fam�lia?</td>
				<td class="answer1"><xsl:value-of select="veioEncaminhadoPorAlgumPostodeSaude" /></td>
			</tr>
			<xsl:if test="veioEncaminhadoPorAlgumPostodeSaude[. = 'sim']">
				<tr>
					<td class="title1">De qual posto?</td>
					<td class="answer1"><xsl:value-of select="deQualPostoDeSaudeFoiEncaminhado" /></td>
				</tr>
			</xsl:if>
			<tr>
				<td class="title1">Encaminhado pelo SUS?</td>
				<td class="answer1"><xsl:value-of select="veioEncaminhadoPorUnidadedDeSaudeSUS" /></td>
			</tr>
			<xsl:if test="veioEncaminhadoPorUnidadedDeSaudeSUS[. = 'sim']">
				<tr>
					<td class="title1">De qual posto?</td>
					<td class="answer1"><xsl:value-of select="deQualPostoDeSaudeDoSUSFoiEncaminhado" /></td>
				</tr>
			</xsl:if>
			<tr>
				<td class="title1">Encaminhado por unidade particular?</td>
				<td class="answer1"><xsl:value-of select="veioEncaminhadoPorUnidadedDeSaudeParticular" /></td>
			</tr>
			<xsl:if test="veioEncaminhadoPorUnidadedDeSaudeParticular[. = 'sim']">
				<tr>
					<td class="title1">De qual posto?</td>
					<td class="answer1"><xsl:value-of select="deQualPostoDeSaudeparticularFoiEncaminhado" /></td>
				</tr>
			</xsl:if>
			<tr>
				<td class="title1">Decidiu sozinho?</td>
				<td class="answer1"><xsl:value-of select="decidiuSozinhoPorAuxilioMedico" /></td>
			</tr>
			<xsl:if test="veioEncaminhadoPorUnidadedDeSaudeParticular[. = 'sim']">
				<tr>
					<td class="title1">Porque?</td>
					<td class="answer1"><xsl:value-of select="porqueDecidiuSozinhoPorAuxilioMedico" /></td>
				</tr>
			</xsl:if>
			<tr>
				<td class="title2">Foi encaminhado para qual setor?</td>
				<td class="answer2"><xsl:value-of select="encaminhadoParaQualSetorDaPoliclinica" /></td>
			</tr>
			<tr>
				<td class="title1">Fez algum tratamento para tosse recente?</td>
				<td class="answer1"><xsl:value-of select="algumTratamentoParaTosseRecente" /></td>
			</tr>
			<xsl:if test="veioEncaminhadoPorUnidadedDeSaudeParticular[. = 'sim']">
				<tr>
					<td class="title1">Qual?</td>
					<td class="answer1"><xsl:value-of select="qualFoiTratamentoRecenteFeito" /></td>
				</tr>
				<tr>
					<td class="title1">Quanto durou?</td>
					<td class="answer1"><xsl:value-of select="quantoDiasDurouTratamentoRecenteFeito" /></td>
				</tr>
			</xsl:if>
			<tr>
				<td class="title2">Trouxe Raio-X de torax?</td>
				<td class="answer2"><xsl:value-of select="trouxeRXdeTorax" /></td>
			</tr>
			<tr>
				<td class="title1">Trouxe resultado de Raio-X de torax?</td>
				<td class="answer1"><xsl:value-of select="trouxeAlgumResultadoDeRXdeTorax" /></td>
			</tr>
			<tr>
				<td class="title2">Trouxe material de escarro?</td>
				<td class="answer2"><xsl:value-of select="trouxeMaterialDeExacarro" /></td>
			</tr>			
			<tr>
				<td class="title2">Trouxe resultado de material de escarro?</td>
				<td class="answer2"><xsl:value-of select="trouxeAlgumResultadoDeMaterialDeExacarro" /></td>
			</tr>
			<tr>
				<td class="title2">Trouxe resultado de bi�psia?</td>
				<td class="answer2"><xsl:value-of select="trouxeAlgumResultadoDeBiopasia" /></td>
			</tr>
			<tr>
				<td class="title1">Trouxe algum outro resultado?</td>
				<td class="answer1"><xsl:value-of select="trouxeAlgumOutroResultado" /></td>
			</tr>
			<xsl:if test="veioEncaminhadoPorUnidadedDeSaudeParticular[. = 'sim']">
				<tr>
					<td class="title1">Qual?</td>
					<td class="answer1"><xsl:value-of select="qualOutroResultado" /></td>
				</tr>
			</xsl:if>
<!-- Fim Perguntas finais de enfermagem -->			

			<tr>
				<td class="title1">Desfecho da consulta inicial:</td>
				<td class="answer1"><xsl:value-of select="desfechoConsultaInicial" /></td>
			</tr>
			
			<xsl:if test="desfechoConsultaInicial[. = 'outra_especialidade']">
				<tr>
					<td class="title1">Especifica��o:</td>
					<td class="answer1"><xsl:value-of select="outra_esp" /></td>
				</tr>			
			</xsl:if>
			
			<xsl:if test="desfechoConsultaInicial[. = 'outros']">
				<tr>
					<td class="title1">Especifica��o:</td>
					<td class="answer1"><xsl:value-of select="outro_desfecho" /></td>
				</tr>			
			</xsl:if>
			
			<tr>
				<td class="title2">Inclus�o:</td>
				<td class="answer2"><xsl:value-of select="inclusao" /></td>
			</tr>
			<xsl:if test="inclusao[. = 'sim']">
				<tr>
				<td class="title2">Motivo:</td>
				<td class="answer2"><xsl:value-of select="criteriosInclusao" /> - <xsl:value-of select="concat(dia_termoConsentimento,'/',mes_termoConsentimento,'/',ano_termoConsentimento)" /></td>
				</tr>
			
				<tr>
					<td class="title1" rowspan="2">Data da coleta dos DOIS esp�cimes respirat�rios:</td>
					<td class="answer1">#1 - <xsl:value-of select="dia_coleta1" />/<xsl:value-of select="mes_coleta1" />/<xsl:value-of select="ano_coleta1" /> - <xsl:value-of select="coleta1" /></td>
				</tr>
				<tr>
					<td class="answer1">#2 - <xsl:value-of select="dia_coleta2" />/<xsl:value-of select="mes_coleta2" />/<xsl:value-of select="ano_coleta2" /> - <xsl:value-of select="coleta2" /></td>
				</tr>
				<tr>
					<td class="title2">Resultado da leitura (mil�metros de endura��o):</td>
					<td class="answer2"><xsl:value-of select="resultadoLeitura" /></td>
				</tr>
				<tr>
					<td class="title1">Data da aplica��o da prova tubercul�nica:</td>
					<td class="answer1"><xsl:value-of select="dia_aplicacao" />/<xsl:value-of select="mes_aplicacao" />/<xsl:value-of select="ano_aplicacao" /></td>
				</tr>
				<tr>
					<td class="title2">Data da leitura:</td>
					<td class="answer2"><xsl:value-of select="dia_leitura" />/<xsl:value-of select="mes_leitura" />/<xsl:value-of select="ano_leitura" /></td>
				</tr>
				<tr>
					<td class="title1">PT primeira dose Leitor:</td>
					<td class="answer1"><xsl:value-of select="PTprimeiraDose" /></td>
				</tr>
			</xsl:if>
			<tr>
				<td class="title2">Cicatriz da BCG presente?</td>
				<td class="answer2"><xsl:value-of select="cicatrizBCG" /></td>
			</tr>
			<tr>
				<td class="title1">Observa��es:</td>
				<td class="answer1"><xsl:value-of select="observacoes" /></td>
			</tr>
			<tr>
				<td class="title2"><xsl:value-of select="concat('Avaliado pelo(a) enfermeiro(a): ', avaliador)" /></td>
				<td class="answer2">Data da avalia��o: <xsl:value-of select="dia_inclusao" />/<xsl:value-of select="mes_inclusao" />/<xsl:value-of select="ano_inclusao" />
					<xsl:value-of select="concat(' ', hora_inclusao)" />
				</td>
			</tr>
</xsl:template>


<!-- Question�rio custos: Parte A -->

<xsl:template match="custosA">
			<tr>
				<td class="title1">Onde mora?</td>
				<td class="answer1"><xsl:value-of select="ondeMora" /></td>
			</tr>
			<tr>
				<td class="title2">Como veio ao posto?</td>
				<td class="answer2"><xsl:value-of select="transporte" /></td>
			</tr>
			<tr>
				<td class="title2">Quanto custou o transporte?</td>
				<td class="answer2"><xsl:value-of select="custoTransporte" /></td>
			</tr>
			<tr>
				<td class="title1">Est� acompanhado? Por quantas pessoas?</td>
				<td class="answer1"><xsl:value-of select="acompanhado" />. <xsl:value-of select="numeroAcompanhantes" /></td>
			</tr>
			<tr>
				<td class="title2">Que horas saiu de casa?</td>
				<td class="answer1"><xsl:value-of select="horaSaidaCasa" />:<xsl:value-of select="minutoSaidaCasa" /></td>
			</tr>
			<tr>
				<td class="title1">Que horas chegou no posto?</td>
				<td class="answer1"><xsl:value-of select="horaChegadaPosto" />:<xsl:value-of select="minutoChegadaPosto" /></td>
			</tr>
			<tr>
				<td class="title2">Que horas viu o m�dico?</td>
				<td class="answer2"><xsl:value-of select="horaMedico" />:<xsl:value-of select="minutoMedico" /></td>
			</tr>
			<tr>
				<td class="title1">Quanto tempo levou desde que saiu de casa?</td>
				<td class="answer1"><xsl:value-of select="horaTotal" />:<xsl:value-of select="minutoTotal" /></td>
			</tr>
			<tr>
				<td class="title2">Se o paciente mora fora da cidade do Rio de Janeiro: Amanh� ter� que voltar para trazer outra amostra de escarro. Onde vai passar a noite? </td>
				<td class="answer2"><xsl:value-of select="pernoite" /></td>
			</tr>
			<tr>
				<td class="title1">Se o paciente n�o passar a noite em casa, ter� que pagar o pernoite?</td>
				<td class="answer1"><xsl:value-of select="pagarPernoite" /></td>
			</tr>
			<tr>
				<td class="title1">Quanto dever� gastar?</td>
				<td class="answer1"><xsl:value-of select="custoPernoite" /></td>
			</tr>
			<tr>
				<td class="title2">Se o paciente n�o tiver que pagar: trouxe algo para seus amigos?</td>
				<td class="answer2"><xsl:value-of select="trouxeAlgoAmigos" /></td>
			</tr>
			<tr>
				<td class="title2">Quanto custou?</td>
				<td class="answer2"><xsl:value-of select="custoAmigos" /></td>
			</tr>
			<tr>
				<td class="title1">Desde que saiu de casa, comeu ou bebeu alguma coisa?</td>
				<td class="answer1"><xsl:value-of select="comeuBebeu" /></td>
			</tr>
			<tr>
				<td class="title1">Quanto custou?</td>
				<td class="answer1"><xsl:value-of select="custoComidaBebida" /></td>
			</tr>
			<tr>
				<td class="title2">Teve que pagar algo aqui no posto?</td>
				<td class="answer2"><xsl:value-of select="pagarPosto" /></td>
			</tr>
			<tr>
				<td class="title2">Quanto custou?</td>
				<td class="answer2"><xsl:value-of select="custoPosto" /></td>
			</tr>
			<tr>
				<td class="title1">Profiss�o:</td>
				<td class="answer1"><xsl:value-of select="profissao" /></td>
			</tr>
			<tr>
				<td class="title2">Se o paciente for um estudante, ele perdeu aula hoje?</td>
				<td class="answer2"><xsl:value-of select="estudantePerdeuAula" /></td>
			</tr>
			<tr>
				<td class="title1">Deixou de ganhar dinheiro hoje para poder vir ao posto?</td>
				<td class="answer1"><xsl:value-of select="deixouGanharDinheiro" /></td>
			</tr>
			<tr>
				<td class="title1">Quanto deixou de ganhar?</td>
				<td class="answer1"><xsl:value-of select="quantoDeixouGanhar" /></td>
			</tr>
			<tr>
				<td class="title2">Se o paciente estiver acompanhado: Quem pagou pela bebida, comida, transporte, hotel, etc? O paciente ou seus acompanhantes?</td>
				<td class="answer2"><xsl:value-of select="quemArcouCustos" /></td>
			</tr>
			<tr>
				<td class="title2">Quanto voc� gastou com seu acompanhante?</td>
				<td class="answer2"><xsl:value-of select="gastoAcompanhante" /></td>
			</tr>
			<tr>
				<td class="title2">Observa��es:</td>
				<td class="answer2"><xsl:value-of select="observacoes" /></td>
			</tr>
			<tr>
				<td class="evaluated">Avaliado pelo(a) enfermeiro(a): <xsl:value-of select="avaliador" /></td>
				<td class="evaluated">Data da avalia��o: <xsl:value-of select="diaCadastro" />/<xsl:value-of select="mesCadastro" />/<xsl:value-of select="anoCadastro" /></td>
			</tr>
</xsl:template>


<!-- Consulta m�dica -->

<xsl:template match="consultaMedica">
			
			<tr>
				<td class="title1">INH:</td>
				<td class="answer1"><xsl:value-of select="inh" /></td>
			</tr>
			<tr>
				<td class="title2">RIF:</td>
				<td class="answer2"><xsl:value-of select="rif" /></td>
			</tr>
			<tr>
				<td class="title1">Qual esquema?</td>
				<td class="answer1"><xsl:value-of select="qualEsquema" /></td>
			</tr>
			<tr>
				<td class="title4" colspan="2">Quimioprofilaxia Pr�via para TB</td>
			</tr>
			
			<tr>
				<td class="title1">Quimioprofilaxia:</td>
				<td class="answer1"><xsl:value-of select="quimioprofilaxia" /></td>
			</tr>
			<tr>
				<td class="title1">Usou INH?</td>
				<td class="answer1"><xsl:value-of select="inhCagePositivo" /></td>
			</tr>
			<tr>
				<td class="title1">Usou RIF?</td>
				<td class="answer1"><xsl:value-of select="rifCagePositivo" /></td>
			</tr>
			<!--
			<tr>
				<td class="title1">Se Cage positivo, usou INH?</td>
				<td class="answer1"><xsl:value-of select="inhCagePositivo" /></td>
			</tr>
			<tr>
				<td class="title1">Se Cage positivo, usou RIF?</td>
				<td class="answer1"><xsl:value-of select="rifCagePositivo" /></td>
			</tr>
			-->
			<tr>
				<td class="title1">Data da quimioprofilaxia:</td>
				<td class="answer1"><xsl:value-of select="mes_quimio" />/<xsl:value-of select="ano_quimio" /></td>
			</tr>
			<tr>
				<td class="title1">Desfecho:</td>
				<td class="answer1"><xsl:value-of select="desfechoQuimio" /></td>
			</tr>
			
			
			<tr>
				<td class="title4" colspan="2">HIV/AIDS</td>
			</tr>
			
			
			<tr>
				<td class="title1">HIV teste:</td>
				<td class="answer1"><xsl:value-of select="testeHIV" /></td>
			</tr>
			<tr>
				<td class="title2">Data do Anti-HIV:</td>
				<td class="answer2"><xsl:value-of select="dia_antihiv" />/<xsl:value-of select="mes_antihiv" />/<xsl:value-of select="ano_antihiv" /></td>
			</tr>
			<tr>
				<td class="title1">Comorbidades:</td>
				<td class="answer1">
				<xsl:for-each select="comorbidades"><xsl:value-of select="." />. </xsl:for-each>
				<xsl:value-of select="outrascomorbidades" /></td>
			</tr>
			
			
			<tr>
				<td class="title4" colspan="2">Avalia��o cl�nica</td>
			</tr> 
			
			<tr>
				<td class="title1">Exame F�sico Normal:</td>
				<td class="answer1"><xsl:value-of select="exameFisico" /></td>
			</tr>
			
			<tr>
				<td class="title1">Altera��es no exame f�sico:</td>
				<td class="answer1"><xsl:value-of select="alteracoesNoExameFisico" /></td>
			</tr>
			
			<tr>
				<td class="title1">Probabilidade de TB ativa: </td>
				<td class="answer1"><xsl:value-of select="probTBativa" /></td>
			</tr>
			<tr>
				<td class="title2">Probabilidade do diagn�stico de TB pulmonar ativa sem avaliar RX de t�rax ou BAAR:</td>
				<td class="answer2"><xsl:value-of select="porcentagemProbTBsemRXsemBAAR" /></td>
			</tr>
			
			<tr>
				<td class="title4" colspan="2">RX de t�rax</td>
			</tr>
			
			<tr>
				<td class="title1">Probabilidade de TB ativa ao avaliar o RXT:</td>
				<td class="answer1"><xsl:value-of select="probTBativaComRX" /></td>
			</tr>
			<tr>
				<td class="title2">Cavita��o:</td>
				<td class="answer2"><xsl:value-of select="cavitacao" /></td>
			</tr>
			<tr>
				<td class="title2">Padr�o t�pico (infiltrado em lobo(s) superior(es) e/ou segmento apical de lobo inferior):</td>
				<td class="answer2"><xsl:value-of select="padraoTipico" /></td>
			</tr>
			<tr>
				<td class="title2">Compat�vel (alargamento mediastinal ou linf. hilar, padr�o miliar,ou derrame pleural):</td>
				<td class="answer2"><xsl:value-of select="compativel" /></td>
			</tr>
			<tr>
				<td class="title2">At�pico (qualquer outro padr�o):</td>
				<td class="answer2"><xsl:value-of select="atipico" /></td>
			</tr>
			<tr>
				<td class="title2">NSA</td>
				<td class="answer2"><xsl:value-of select="nsa" /></td>
			</tr>
			<tr>
				<td class="title1">Em caso de baixa probabilidade de TB ativa:</td>
				<td class="answer1"><xsl:value-of select="casoBaixaProbabilidade" /></td>
			</tr>
			<tr>
				<td class="title2">Data do RX:</td>
				<td class="answer2"><xsl:value-of select="dia_rx" />/<xsl:value-of select="mes_rx" />/<xsl:value-of select="ano_rx" /></td>
			</tr>
			<tr>
				<td class="title1">Diagn�stico de probabilidade tendo informa��o sobre o RX de t�rax mas sem conhecimento dos resultados bacteriol�gicos:</td>
				<td class="answer1"><xsl:value-of select="diagnosticoProbabilidadeRX" /></td>
			</tr>
			<tr>
				<td class="title2">Probabilidade do diagn�stico de TB pulmonar ativa com a avalia��o do RX de t�rax e SEM  RESULTADO DA BACILOSCOPIA (BAAR):</td>
				<td class="answer2"><xsl:value-of select="probabilidadeTBcomRXsemBAAR" /></td>
			</tr>
			<tr>
				<td class="title1">Resultado da Baciloscopia 1:</td>
				<td class="answer1"><xsl:value-of select="resultadoBaciloscopia1" />. <xsl:value-of select="casoPositivo1" />.</td>
			</tr>
			<tr>
				<td class="title1">Resultado da Baciloscopia 2:</td>
				<td class="answer1"><xsl:value-of select="resultadoBaciloscopia2" />. <xsl:value-of select="casoPositivo2" />.</td>
			</tr>
			<tr>
				<td class="title2">Caso as duas baciloscopias iniciais sejam negativas qual seria o diagn�stico de probabilidade de TB?</td>
				<td class="answer2"><xsl:value-of select="diagnosticoProbabilidadeCasoDuasNegativas" /></td>
			</tr>
			<tr>
				<td class="title1">Probabilidade do diagn�stico de TB pulmonar ativa com a avalia��o do RX de t�rax e do BAAR:</td>
				<td class="answer1"><xsl:value-of select="probabilidadeTBcomRXcomBAAR" /></td>
			</tr>
			<tr>
				<td class="title2">Desfecho consulta inicial:</td>
				<td class="answer2"><xsl:value-of select="desfechoConsultaInicial" /></td>
			</tr>
			<tr>
				<td class="title2">Em caso de tratamento para TB, qual?</td>
				<td class="answer2"><xsl:value-of select="casoTratamentoTB" /></td>
			</tr>
			<tr>
				<td class="title2">Fatores de risco para TBP MDR:</td>
				<td class="answer2"><xsl:value-of select="fatoresRisco" /></td>
			</tr>
			<tr>
				<td class="title2">Observa��es:</td>
				<td class="answer2"><xsl:value-of select="observacoes" /></td>
			</tr>
			<tr>
				<td class="evaluated">Avaliado pelo(a) m�dico(a): <xsl:value-of select="avaliador" /></td>
				<td class="evaluated">Data da avalia��o: <xsl:value-of select="dia_inclusao" />/<xsl:value-of select="mes_inclusao" />/<xsl:value-of select="ano_inclusao" /></td>
			</tr>

                        <tr>
                                <td class="title2">Cadastrado por:</td>
                                <td class="answer2"><xsl:value-of select="quemCadastrou" /></td>
                        </tr>


</xsl:template>


<!-- Question�rio custos: Partes B e C -->

<xsl:template match="custosBeC">
			
			<!-- Parte B -->
			
			<tr>
				<td class="title1">Tem o resultado dos exames?</td>
				<td class="answer1"><xsl:value-of select="resultadoExames" /></td>
			</tr>
			<tr>
				<td class="title2">Quantas vezes veio ao posto para pegar os resultados dos exames?</td>
				<td class="answer2"><xsl:value-of select="quantasVezesVeioPosto" /></td>
			</tr>
			<tr>
				<td class="title1">Como veio ao posto? Em qual transporte?</td>
				<td class="answer1"><xsl:value-of select="comoVeioPosto" /></td>
			</tr>
			<tr>
				<td class="title1">Se n�o veio a p� quanto custou o transporte?</td>
				<td class="answer1"><xsl:value-of select="custoTransporte" /></td>
			</tr>
			<tr>
				<td class="title2">Voc� est� acompanhado? Por quantas pessoas?</td>
				<td class="answer2"><xsl:value-of select="acompanhado" />. <xsl:value-of select="numeroAcompanhantes" /></td>
			</tr>
			<tr>
				<td class="title1">Que horas saiu de casa?</td>
				<td class="answer1"><xsl:value-of select="horaSaidaCasa" />:<xsl:value-of select="minutoSaidaCasa" /></td>
			</tr>
			<tr>
				<td class="title2">Que horas chegou no posto?</td>
				<td class="answer2"><xsl:value-of select="horaChegadaPosto" />:<xsl:value-of select="minutoChegadaPosto" /></td>
			</tr>
			<tr>
				<td class="title1">Que horas viu o m�dico?</td>
				<td class="answer1"><xsl:value-of select="horaMedico" />:<xsl:value-of select="minutoMedico" /></td>
			</tr>
			<tr>
				<td class="title2">Quanto tempo levou desde que saiu de casa?</td>
				<td class="answer2"><xsl:value-of select="horaTotal" />:<xsl:value-of select="minutoTotal" /></td>
			</tr>
			<tr>
				<td class="title1">Quando teve que trazer a segunda amostra de escarro h� alguns dias, em que hor�rio escarrou no potinho?</td>
				<td class="answer1"><xsl:value-of select="horaEscarro" />:<xsl:value-of select="minutoEscarro" /></td>
			</tr>
			<tr>
				<td class="title2">Que horas acordou no dia de escarrar pela segunda vez no potinho?</td>
				<td class="answer2"><xsl:value-of select="horaAcordouEscarro" />:<xsl:value-of select="minutoAcordouEscarro" /></td><!-- ............... -->
			</tr>
			<tr>
				<td class="title1">Recebeu uma receita com antibi�ticos?</td>
				<td class="answer1"><xsl:value-of select="receitaAntibioticos" /></td>
			</tr>
			<tr>
				<td class="title2">Pediu para fazer um RX?</td>
				<td class="answer2"><xsl:value-of select="pediuRX" /></td>
			</tr>
			<tr>
				<td class="title1">Desde que saiu de casa, comeu ou bebeu alguma coisa?</td>
				<td class="answer1"><xsl:value-of select="comeuBebeu" /></td>
			</tr>
			<tr>
				<td class="title1">Quanto custou?</td>
				<td class="answer1"><xsl:value-of select="custoComidaBebida" /></td>
			</tr>
			<tr>
				<td class="title2">Teve que pagar algo aqui no posto?</td>
				<td class="answer2"><xsl:value-of select="pagarPostoB" /></td>
			</tr>
			<tr>
				<td class="title2">Quanto custou?</td>
				<td class="answer2"><xsl:value-of select="custoPostoB" /></td>
			</tr>
			<tr>
				<td class="title1">Deixou de ganhar dinheiro hoje para poder vir ao posto?</td>
				<td class="answer1"><xsl:value-of select="deixouGanharDinheiro" /></td>
			</tr>
			<tr>
				<td class="title1">Quanto deixou de ganhar?</td>
				<td class="answer1"><xsl:value-of select="quantoDeixouGanhar" /></td>
			</tr>
			<tr>
				<td class="title2">J� sabe o resultado dos exames de escarro?</td>
				<td class="answer2"><xsl:value-of select="resultadoExameEscarro" /></td>
			</tr>
			<tr>
				<td class="title1">Se o paciente tiver TB: Foi registrado no programa de tratamento de TB?</td>
				<td class="answer1"><xsl:value-of select="programaTB" /></td>
			</tr>
			
			<!-- Parte C -->
			
			<tr>
				<td class="title2">Teve que pagar algo aqui no posto?</td>
				<td class="answer2"><xsl:value-of select="pagarPostoC" /></td>
			</tr>
			<tr>
				<td class="title2">Quanto custou?</td>
				<td class="answer2"><xsl:value-of select="custoPostoC" /></td>
			</tr>
			<tr>
				<td class="title1">H� quanto tempo estava sentindo-se diferente ou doente, antes de vir ao posto?</td>
				<td class="answer1"><xsl:value-of select="tempoDoente" /> semanas.</td>
			</tr>
			<tr>
				<td class="title2">Antes de ser diagnosticado no posto, voc� foi a alguma outra unidade de sa�de?</td>
				<td class="answer2"><xsl:value-of select="outraUnidadeSaude" /></td>
			</tr>
			<tr>
				<td class="title2">Este local era:</td>
				<td class="answer2"><xsl:value-of select="naturezaLocal" />. <xsl:value-of select="qual_outro" /></td>
			</tr>
			<tr>
				<td class="evaluated">Avaliado pelo(a) enfermeiro(a): <xsl:value-of select="avaliador" /></td>
				<td class="evaluated">Data da avalia��o: <xsl:value-of select="diaCadastro" />/<xsl:value-of select="mesCadastro" />/<xsl:value-of select="anoCadastro" /></td>
			</tr>
</xsl:template>


<!-- Follow Up -->

<xsl:template match="followUp">
			<tr>
				<td class="title1">Crit�rio de Entrada:</td>
				<td class="answer1"><xsl:value-of select="criterioEntrada" /></td>
			</tr>
			<tr>
				<td class="title2">Tratamento prescrito para TB:</td>
				<td class="answer2"><xsl:value-of select="tratamentoPrescritoTB" /></td>
			</tr>
			<tr>
				<td class="title2">Data do in�cio:</td>
				<td class="answer2"><xsl:value-of select="inicio_dia" />/<xsl:value-of select="inicio_mes" />/<xsl:value-of select="inicio_ano" /></td>
			</tr>
			<tr>
				<td class="title1">F�rmacos utilizados:</td>
				<td class="answer1">
				<xsl:for-each select="tratamentoPrescritoTBFarmacos"><xsl:value-of select="." />. </xsl:for-each>
				<xsl:value-of select="farmacos7" /></td>
			</tr>
			<tr>
				<td class="title1">Rea��o adversa dos tuberculost�ticos?</td>
				<td class="answer1"><xsl:value-of select="reacoesAdversasTuberculostaticos" /></td>
			</tr>
			<tr>
				<td class="title1">Maiores:</td>
				<td class="answer1">
				<xsl:for-each select="reacoesAdversasTuberculostaticosMaiores"><xsl:value-of select="." />. </xsl:for-each></td>
			</tr>
			<tr>
				<td class="title1">Menores:</td>
				<td class="answer1">
				<xsl:for-each select="reacoesAdversasTuberculostaticosMenores"><xsl:value-of select="." />. </xsl:for-each></td>
			</tr>
			<tr>
				<td class="title2">Houve �bito?</td>
				<td class="answer2"><xsl:value-of select="obito" /></td>
			</tr>
			<tr>
				<td class="title2">Qual a causa?</td>
				<td class="answer2"><xsl:value-of select="casoObito" /></td>
			</tr>
			<tr>
				<td class="title1">Mudan�a de esquema de tratamento para TB?</td>
				<td class="answer1"><xsl:value-of select="mudancaEsquemaTratamentoTB" /></td>
			</tr>
			<tr>
				<td class="title2">Data da mudan�a:</td>
				<td class="answer2"><xsl:value-of select="mudanca_mes" />/<xsl:value-of select="mudanca_ano" /></td>
			</tr>
			<tr>
				<td class="title1">F�rmacos utilizados:</td>
				<td class="answer1">
				<xsl:for-each select="mudancaFarmacos"><xsl:value-of select="." />. </xsl:for-each>
				<xsl:value-of select="farmacos14" /></td>
			</tr> 
			<tr>
				<td class="title1">Motivo:</td>
				<td class="answer1">
				<xsl:value-of select="mudancaMotivo" />.<xsl:value-of select="motivo" /></td>
			</tr>
			<tr>
				<td class="title2">Tosse diminu�da:</td>
				<td class="answer2"><xsl:value-of select="tosseDiminuida" /></td>
			</tr>
			<tr>
				<td class="title1">Peso atual:</td>
				<td class="answer1"><xsl:value-of select="concat(pesoAtual90dias, ' ', pesoAtual90dias/@unidade)" /></td>
			</tr>
			<tr>
				<td class="title1">Altera��es evolutivas no exame f�sico:</td>
				<td class="answer1"><xsl:value-of select="alteracoesEvolutivasNoExameFisico" /></td>
			</tr>
			<tr>
				<td class="title2">Probabilidade de TB ativa ao avaliar o RXT:</td>
				<td class="answer2"><xsl:value-of select="probabilidadeTBAtivaAposEstudoRX" /></td>
			</tr>
			<tr>
				<td class="title1">Cavita��o:</td>
				<td class="answer1"><xsl:value-of select="cavitacao90dias" /></td>
			</tr>
			<tr>
				<td class="title1">Padr�o t�pico (infiltrado em lobo(s) superior(es) e/ou segmento apical de lobo inferior):</td>
				<td class="answer1"><xsl:value-of select="padraoTipico90dias" /></td>
			</tr>
			<tr>
				<td class="title1">Compat�vel (alargamento mediastinal ou linf. hilar , padr�o miliar,ou derrame pleural):</td>
				<td class="answer1"><xsl:value-of select="compativel90dias" /></td>
			</tr>
			<tr>
				<td class="title1">At�pico (qualquer outro padr�o):</td>
				<td class="answer1"><xsl:value-of select="atipico90dias" /></td>
			</tr>
			<tr>
				<td class="title1">NSA</td>
				<td class="answer1"><xsl:value-of select="NSA90dias" /></td>
			</tr>
			<tr>
				<td class="title2">Em caso de baixa probabilidade de TB ativa:</td>
				<td class="answer2"><xsl:value-of select="casoBaixaProbabilidade90dias" /></td>
			</tr>
			<tr>
				<td class="title2">Data do RX:</td>
				<td class="answer2"><xsl:value-of select="rx_dia" />/<xsl:value-of select="rx_mes" />/<xsl:value-of select="rx_ano" /></td>
			</tr>
			<tr>
				<td class="title2">Follow up do RX de T�rax (compare com o RXT inicial como o atual):</td>
				<td class="answer2"><xsl:value-of select="followUpRXTorax" /></td>
			</tr>
			<tr>
				<td class="title1">HIV teste:</td>
				<td class="answer1"><xsl:value-of select="testeHIV90dias" /></td>
			</tr>
			<tr>
				<td class="title2">Data do Anti-HIV:</td>
				<td class="answer2"><xsl:value-of select="antihiv_dia" />/<xsl:value-of select="antihiv_mes" />/<xsl:value-of select="antihiv_ano" /></td>
			</tr>
			<tr>
				<td class="title1">Diagn�stico 90 dias:</td>
				<td class="answer1"><xsl:value-of select="diagnostico90dias" />.</td>
			</tr>
			<tr>
				<td class="title2">Em caso de outro diagn�stico diferente de TB, qual?</td>
				<td class="answer2"><xsl:value-of select="diagnosticoDiferenteTB" />. <xsl:value-of select="outro_diagnostico_sim" /></td>
			</tr>
			<tr>
				<td class="title1">Diagn�stico Final:</td>
				<td class="answer1"><xsl:value-of select="diagnosticoFinal" /></td>
			</tr>
			<tr>
				<td class="title2">Observa��es:</td>
				<td class="answer2"><xsl:value-of select="observacoes" /></td>
			</tr>
			<tr>
				<td class="evaluated">Avaliado pelo(a) m�dico(a): <xsl:value-of select="avaliadorMedicoFollowUp" /></td>
				<td class="evaluated">Data da avalia��o: <xsl:value-of select="dia_FollowUp" />/<xsl:value-of select="mes_FollowUp" />/<xsl:value-of select="ano_FollowUp" /></td>
			</tr>
</xsl:template>

</xsl:stylesheet>
